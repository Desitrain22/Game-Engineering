#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, modelMatrix2, projectionMatrix, modelMatrix3;

glm::vec3 player1_movement, player2_movement, player1_position, player2_position;


GLuint playerTextureID;
GLuint playerTextureID2;
GLuint playerTextureID3;

GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

    if (image == NULL) {
        std::cout << "Unable to load image" << std::endl;
        assert(false);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(image);
    return textureID;
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);//^OPen window, <- set context
    SDL_GL_MakeCurrent(displayWindow, context);//Make that window^ the current context we refer
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480); //what scope we looking
    

    //shaders for handling textures
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl"); //load shaders

    //playerTextureID = LoadTexture("player.png"); //load's player image to use
    
    viewMatrix = glm::mat4(1.0f);
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix2, glm::vec3(3.0f, 3.0f, 0.0f));

    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(-3.0f, -3.0f, 0.0f));

    modelMatrix3 = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f); //orthographic view

    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);  
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    playerTextureID = LoadTexture("tileset.png");
    playerTextureID2 = LoadTexture("tileset.png");
    playerTextureID3 = LoadTexture("ball.png");
}

void ProcessInput() {
    SDL_Event event;

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    player1_movement = glm::vec3(0.0);
    player2_movement = glm::vec3(0.0);
    
    while (SDL_PollEvent(&event)) {


        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;
        }
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		if (player1_position.x >= -1.5)
		{
            player1_movement.x = -3;
		}
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		if (player1_position.x <= 7.0)
		{
            player1_movement.x += 3;
		}
	}
	if (keys[SDL_SCANCODE_LCTRL])
	{
		if (player2_position.x >= -7.5f)
		{
			player2_movement.x = -3;
		}
	}
	if (keys[SDL_SCANCODE_LALT])
	{
		if (player2_position.x <= 1.0)
		{
			player2_movement.x = 3;
		}
	}
}

float lastTicks = 0.0f; //must be declared globally rather than inside Update()

void Update() {

    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    player1_position += player1_movement * deltaTime;
    player2_position += player2_movement * deltaTime;


    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.0f, 3.0f, 0.0f));
    modelMatrix = glm::translate(modelMatrix, player2_position);

    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(-3.0f, -3.0f, 0.0f));
    modelMatrix2 = glm::translate(modelMatrix2, player1_position);



    modelMatrix3 = glm::mat4(1.0f);
    //modelMatrix3 = glm::translate(modelMatrix3, glm::vec3(0.0f, -3.0f, 0.0f));
    
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    program.SetModelMatrix(modelMatrix);

    float vertices[] = { -1.0f, -0.5f, 1.0f, -0.5f, 1.0f, 0.0f, -1.0f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f }; //vertices of the triangle.
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    float vertices2[] = { -0.25f, -0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f};

    //rendering
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);

    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);

    //drawing the paddles
    program.SetModelMatrix(modelMatrix);

    glBindTexture(GL_TEXTURE_2D, playerTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    program.SetModelMatrix(modelMatrix2);

    glBindTexture(GL_TEXTURE_2D, playerTextureID2);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //drawing ball
    
    program.SetModelMatrix(modelMatrix3);

    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices2);
    glEnableVertexAttribArray(program.positionAttribute);
    
    glBindTexture(GL_TEXTURE_2D, playerTextureID3);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);

    
    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }
    
    Shutdown();
    return 0;
}
