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
glm::mat4 viewMatrix, modelMatrix, modelMatrix2, projectionMatrix;

float player_x = 0; //mario x movement
float player_y = 0; //mario y movement to jump

float player_rotate = 0; //rotation of mega man

GLuint playerTextureID;
GLuint playerTextureID2;

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
    displayWindow = SDL_CreateWindow("Project one: Mario jumps over megaman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
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
    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(-5.0f, 0.0f, 0.0f));
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f); //orthographic view
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);  
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    playerTextureID = LoadTexture("megaman.png");
    playerTextureID2 = LoadTexture("mario.png");
}

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
    }
}

float lastTicks = 0.0f;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    player_rotate += 90.0f * deltaTime;
    
    player_x += 1.0f * deltaTime; 

    if (player_x >= 4.0f && player_x < 5.0f )
    {
        player_y += 1.0f * deltaTime;
    }
    else if (player_x >= 5.0f && (player_x < 5.5f))
    {
        player_y -= 2.0f * deltaTime;
    }

    modelMatrix = glm::mat4(1.0f);  
    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(-5.0f, 0.0f, 0.0f));

    modelMatrix = glm::rotate(modelMatrix, glm::radians(player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(player_x, player_y, 0.0f));
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    program.SetModelMatrix(modelMatrix);

    float vertices[] = { -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5, 0.5, -0.5, 0.5 }; //vertices of the triangle.
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    //float vertices2[] = { -5.0f, -0.5f, -4.0f, -0.5f, -4.0f, 0.5f, -5.0f, -0.5f, -4.0f, 0.5f,-5.0f, 0.5f};
    //float texCoords2[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    //rendering and drawing rotating megaman textures
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);

    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);

    //drawing megaman
    program.SetModelMatrix(modelMatrix);

    glBindTexture(GL_TEXTURE_2D, playerTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //drawing mario
    program.SetModelMatrix(modelMatrix2);

    glBindTexture(GL_TEXTURE_2D, playerTextureID2);
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
