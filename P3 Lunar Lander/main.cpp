#include <vector>
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
bool showEndText = false;
bool missionPass = false;


ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, modelMatrix2, modelMatrix3, projectionMatrix;

float rocket_velocity;
float xrand = 2.0f; //I wanted to RNG this but it wasn't working even when I caste to float :/.... I'm also running out of time to submit lol

GLuint rocketTextureID;
GLuint tilesID;
GLuint font;
GLuint tntID;

glm::vec3 rocket_movement, rocket_position;

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(image);
    return textureID;
}

void DrawText(ShaderProgram* program, GLuint fontTextureID, std::string text,
    float size, float spacing, glm::vec3 position)
{
    float width = 1.0f / 16.0f;
    float height = 1.0f / 16.0f;

    std::vector<float> vertices;
    std::vector<float> texCoords;

    for (int i = 0; i < text.size(); i++) {

		int index = (int)text[i];
		float offset = (size + spacing) * i;
		float u = (float)(index % 16) / 16.0f;
		float v = (float)(index / 16) / 16.0f;
		vertices.insert(vertices.end(), {
		offset + (-0.5f * size), 0.5f * size,
		offset + (-0.5f * size), -0.5f * size,
		offset + (0.5f * size), 0.5f * size,
		offset + (0.5f * size), -0.5f * size,
		offset + (0.5f * size), 0.5f * size,
		offset + (-0.5f * size), -0.5f * size,
			});
		texCoords.insert(texCoords.end(), {
		u, v,
		u, v + height,
		u + width, v,
		u + width, v + height,
		u + width, v,
		u, v + height,
			});

	} // end of for loop


	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	program->SetModelMatrix(modelMatrix);

	glUseProgram(program->programID);

	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
	glEnableVertexAttribArray(program->positionAttribute);

	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
	glEnableVertexAttribArray(program->texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, fontTextureID);
	glDrawArrays(GL_TRIANGLES, 0, (int)(text.size() * 6));

	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);
}


float lastTicks = 0.0f;



void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index, int cols, int rows)
{
    float u = (float)(index % cols) / (float)cols;
    float v = (float)(index / cols) / (float)rows;

    float width = 1.0f / (float)cols;
    float height = 1.0f / (float)rows;

    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
    u, v + height, u + width, v, u, v };

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };

    glBindTexture(GL_TEXTURE_2D, textureID);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}



void ProcessInput() {
    SDL_Event event;

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    rocket_movement = glm::vec3(0.0);

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
        rocket_velocity -= 1;
    }
    if (keys[SDL_SCANCODE_RIGHT])
    {
        rocket_velocity += 1;
    }
    if (keys[SDL_SCANCODE_SPACE])
    {
        rocket_velocity = 0;
        rocket_movement = glm::vec3(0.0f);
        rocket_position = glm::vec3(0.0f);
        showEndText = false;
        missionPass = false;
    }

    rocket_movement.x = rocket_velocity * 0.01f;
    rocket_movement.y = -1.0f;
}


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Project 4: Lunar Lander", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);//^OPen window, <- set context
    SDL_GL_MakeCurrent(displayWindow, context);//Make that window^ the current context we refer
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);

    //shaders for handling textures
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl"); //load shaders

    viewMatrix = glm::mat4(1.0f);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix3 = glm::mat4(1.0f);


    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f); //orthographic view
   
    rocket_position = glm::vec3(0.0f);
    rocket_movement = glm::vec3(0.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);  
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    rocketTextureID = LoadTexture("platformerPack_character.png");
    tilesID = LoadTexture("tileset.png");
    tntID = LoadTexture("tnt.png");
    font = LoadTexture("font2.png");
}

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    if (!(rocket_position.y <= -6.0f) && !(abs(rocket_position.x) >= 4.6f))
    {
        rocket_position += rocket_movement * deltaTime;
    }

    else
    {
        showEndText = true;
        if (abs(rocket_position.x) >= 5.0f)
        {
            missionPass = false;
        }
        else if ((rocket_position.x >= 1.5) && (rocket_position.x < 2.5f))
        {
            missionPass = true;
        }
    }


    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 3.5f, 0.0f));    
    modelMatrix = glm::translate(modelMatrix, rocket_position);

    modelMatrix2 = glm::mat4(1.0f);
    modelMatrix2 *= glm::vec4(10.0f, 1.0f, 1.0f, 1.0f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(0.0f, -3.5f, 0.0f));

    modelMatrix3 = glm::mat4(1.0f);
    modelMatrix3 = glm::translate(modelMatrix3, glm::vec3(xrand, -3.5f, 0.0f));
}
void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);



    if (showEndText == true)
    {
        DrawText(&program, font, (missionPass) ? "Success!" : "Retry: Space", 0.75f, -0.25f, glm::vec3(-2.5f, 0.0f, 0.0f));
        program.SetModelMatrix(modelMatrix);
        DrawSpriteFromTextureAtlas(&program, rocketTextureID, (missionPass) ? 2 : 6, 4, 2);
    }
    else
    {
        program.SetModelMatrix(modelMatrix);
        DrawSpriteFromTextureAtlas(&program, rocketTextureID, 0, 4, 2);
    }


    program.SetModelMatrix(modelMatrix2);
    DrawSpriteFromTextureAtlas(&program, tntID, 0, 1, 1);
    
    program.SetModelMatrix(modelMatrix3);
    DrawSpriteFromTextureAtlas(&program, tilesID, 3, 4, 1);

    //float vertices[] = { -5.0, -4.0, 5.0, -4.0, 5.0, -3.0, -5.0, -4.0, 5.0, -3.0, -5.0, -4.0 };
    //float texCoords[] = { 0.0, }

    //glBindTexture(GL_TEXTURE_2D, tntID);

    //glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    //glEnableVertexAttribArray(program.positionAttribute);

    //glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    //glEnableVertexAttribArray(program.texCoordAttribute);

    //glDrawArrays(GL_TRIANGLES, 0, 6);

    //glDisableVertexAttribArray(program->positionAttribute);
    //glDisableVertexAttribArray(program->texCoordAttribute);
    //
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
