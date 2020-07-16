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

#include "Entity.h"

#define ENEMY_COUNT 3

struct GameState {
    Entity* player;
    Entity* enemies;
    Entity* shot;
};
GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;
bool startScreen = true;
bool youWin = false;
bool youLose = false;
ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;
GLuint font;

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

/*void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index, int cols, int rows)
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
}*/


void ProcessInput() {
    SDL_Event event;

    state.player->attackInPlace = false;

    const Uint8* keys = SDL_GetKeyboardState(NULL);


    state.player->movement = glm::vec3(0.0f);

    while (SDL_PollEvent(&event)) {


        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;
        }
    }
    if (youLose || youWin)
    {    }
    else if (!startScreen)
    {
        if (keys[SDL_SCANCODE_UP])
        {
            state.player->animIndices = state.player->animUp;
            state.player->animFrames = 4;
            if (keys[SDL_SCANCODE_SPACE])
            {
                state.player->animIndices = state.player->animUpAtk;
                state.player->animFrames = 2;

                if (state.shot->attackInPlace == false)
                {
                    state.shot->attackInPlace = true;
                    state.shot->animFrames = 0; //Using this to indicate it's direction
                    state.shot->position = state.player->position;
                }
            }
            state.player->movement.y += 1.0f;
        }
        else if (keys[SDL_SCANCODE_DOWN])
        {
            state.player->animFrames = 4;
            state.player->animIndices = state.player->animDown;
            if (keys[SDL_SCANCODE_SPACE])
            {
                state.player->animFrames = 2;
                state.player->animIndices = state.player->animDownAtk;
                if (state.shot->attackInPlace == false)
                {
                    state.shot->attackInPlace = true;
                    state.shot->animFrames = 1; //Using this to indicate it's direction
                    state.shot->position = state.player->position;
                }
            }
            state.player->movement.y += -1.0f;
        }
        else if (keys[SDL_SCANCODE_LEFT] or keys[SDL_SCANCODE_RIGHT])
        {
            state.player->animFrames = 4;
            state.player->animIndices = state.player->animRight;
            if (keys[SDL_SCANCODE_SPACE])
            {
                state.player->animFrames = 2;
                state.player->animIndices = state.player->animRightAtk;
                if (state.shot->attackInPlace == false)
                {
                    state.shot->attackInPlace = true;
                    state.shot->animFrames = 2; //Using this to indicate it's direction
                    state.shot->position = state.player->position;
                }
            }
            if (keys[SDL_SCANCODE_LEFT])
            {
                state.player->movement.x += -1.0f;
            }
            if (keys[SDL_SCANCODE_RIGHT])
            {
                state.player->movement.x += 1.0f;
            }
        }
        else if (keys[SDL_SCANCODE_SPACE])
        {
            state.player->attackInPlace = true;
            state.player->animFrames = 2;
            if ((state.player->animIndices == state.player->animRight) || (state.player->animIndices == state.player->animRightAtk))
            {
                state.player->animIndices = state.player->animRightAtk;
                if (state.shot->attackInPlace == false)
                {
                    /*if (state.player->animIndices == state.player->animRightAtk)
                    {
                        state.player->animIndex = 0;
                    }*/
                    state.shot->attackInPlace = true;
                    state.shot->animFrames = 2; //Using this to indicate it's direction
                    state.shot->position = state.player->position;
                }
            }
            else if ((state.player->animIndices == state.player->animDown) || (state.player->animIndices == state.player->animDownAtk))
            {

                /*if (state.player->animIndices == state.player->animDownAtk)
                {
                    state.player->animIndex = 0;
                }*/
                state.player->animIndices = state.player->animDownAtk;
                if (state.shot->attackInPlace == false)
                {
                    state.shot->attackInPlace = true;
                    state.shot->animFrames = 1; //Using this to indicate it's direction
                    state.shot->position = state.player->position;
                }
            }
            else if ((state.player->animIndices == state.player->animUp) || (state.player->animIndices == state.player->animUpAtk))
            {
                /*
                if (state.player->animIndices == state.player->animUpAtk)
                {
                    state.player->animIndex = 0;
                }*/
                state.player->animIndices = state.player->animUpAtk;
                if (state.shot->attackInPlace == false)
                {
                    state.shot->attackInPlace = true;
                    state.shot->animFrames = 0; //Using this to indicate it's direction
                    state.shot->position = state.player->position;
                }
            }

        }
    }
    else
    {
        if (keys[SDL_SCANCODE_SPACE])
        {            
            startScreen = false;
        }
    }
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Project 5: Rise of the AI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);//^OPen window, <- set context
    SDL_GL_MakeCurrent(displayWindow, context);//Make that window^ the current context we refer
    
#ifdef _WINDOWS
    glewInit();
#endif
  
    glViewport(0, 0, 640, 480);
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl"); //load shaders
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f); //orthographic view 
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);      
    glUseProgram(program.programID);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font = LoadTexture("font2.png");

    state.player = new Entity();
    state.player->position = glm::vec3(1.0, 0.0f, 0.0f);
    state.player->movement = glm::vec3(0.0);
    state.player->speed = 1.0f;
    state.player->textureID = LoadTexture("rotmgmystic.png");
    state.player->rows = 3;
    state.player->cols = 5;
    state.player->animRight = new int[4]{ 4, 3, 2, 3};
    state.player->animRightAtk = new int[2]{ 1, 0 };
    state.player->animDown = new int[4]{ 9, 8, 9, 7 };
    state.player->animDownAtk = new int[2]{ 6, 5 };
    state.player->animUp = new int[4]{ 14, 13, 14, 12 };
    state.player->animUpAtk = new int[2]{ 11, 10 };
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 3;
    state.player->animIndex = 0;
    state.player->animTime = 0;

    state.shot = new Entity();
    state.shot->position = glm::vec3(0.0, 0.0f, 0.0f);
    state.shot->movement = glm::vec3(0.0);
    state.shot->textureID = LoadTexture("shot.png");
    state.shot->speed = 2.0f;
    state.shot->attackInPlace = false; //indicates whether shot active or not

    state.enemies = new Entity[ENEMY_COUNT];
    GLuint enemyTexture = LoadTexture("astronaut3.png");
    
    for (int i = 0; i < 3; i++)
    {
        state.enemies[i].textureID = enemyTexture;
        state.enemies[i].position = glm::vec3(-5.0f, -2.0f + (2.0)*i, 0.0f);
        state.enemies[i].rows = 8;
        state.enemies[i].cols = 13;
        state.enemies[i].movement = glm::vec3(0.0);
        state.enemies[i].speed = 1.0f;
        state.enemies[i].animRight = new int[5]{ 16, 17, 18, 19, 20 }; //Walking Right
        state.enemies[i].animRightAtk = new int[10] {52, 53, 54, 55, 56, 57, 58, 59, 60, 61}; //Attacking 'forward'

        state.enemies[i].animDown = new int[7]{ 91, 92, 93, 94, 95, 96, 97 }; //death animation stored here

        state.enemies[i].animUp = new int[25]{ 0,1,2,3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4,3,2,1,0 }; //Static position stored here
        state.enemies[i].animUpAtk = new int[10]{ 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };

        state.enemies[i].animFrames = 25;
        state.enemies[i].animIndex = 0;
        state.enemies[i].animTime = 0;
        state.enemies[i].attackInPlace = true; //Constant static animation if not moving
    }

    state.enemies[1].animIndices = state.enemies[1].animRight;
    state.enemies[1].animFrames = 5;
    state.enemies[0].animIndices = state.enemies[0].animRightAtk;
    state.enemies[0].animFrames = 10;
    state.enemies[2].animIndices = state.enemies[2].animUpAtk;
    state.enemies[2].animFrames = 10;

    

    

}

float nextMovement;

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    if (state.shot->attackInPlace == true)
    {
        state.shot->timer += deltaTime;

        if (state.shot->animFrames == 0)
        {
            state.shot->movement = glm::vec3(0.0f, 1.0f, 0.0f);
        }
        else if (state.shot->animFrames == 1)
        {
            state.shot->movement = glm::vec3(0.0f, -1.0f, 0.0f);
        }
        else if (state.shot->animFrames == 2)
        {
            state.shot->movement = glm::vec3(-1.0f, 0.0f, 0.0f);
        }


        if (state.shot->timer >= 2.0f)
        {
            state.shot->timer = 0;
            state.shot->attackInPlace = false;
            state.shot->animFrames = 10;
        }
        for (int k = 0; k < 3; k++)
        {
            if (fabs(state.shot->position.x - state.enemies[k].position.x) < .4f)
            {
                if (fabs(state.shot->position.y - state.enemies[k].position.y) < .4f)
                {
                    state.enemies[k].animIndices = state.enemies[k].animDown;
                    state.enemies[k].animFrames = 7;
                    state.enemies[k].animIndex = 0;
                    state.shot->attackInPlace = false;
                }
            }
        }
    }

    state.shot->Update(deltaTime);

    for (int i = 0; i < 3; i++)
    {
        if (state.enemies[i].animIndices == state.enemies[i].animDown)
        {
            if (state.enemies[i].animIndex == 6)
            {
                state.enemies[i].dead = true;
            }
        }
        if (state.enemies[i].animIndices == state.enemies[i].animRight)
        {
            state.enemies[i].movement.x = 1.0f;
            if (state.enemies[i].animIndex == state.enemies[i].animFrames-1)
            {
                state.enemies[i].animIndices = state.enemies[i].animRightAtk;
                state.enemies[i].animFrames = 10;
                state.enemies[i].animIndex = 0;
            }
        }

        else if (state.enemies[i].animIndices == state.enemies[i].animRightAtk)
        {
            state.enemies[i].movement.x = 0.5f;
            if (state.enemies[i].animIndex == state.enemies[i].animFrames-1)
            {
                state.enemies[i].animIndices = state.enemies[i].animUp;
                state.enemies[i].animFrames = 25;
                state.enemies[i].animIndex = 0;
            }
        }

        else if (state.enemies[i].animIndices == state.enemies[i].animUp)
        {
            state.enemies[i].movement.x = 0.0f;
            if (state.enemies[i].animIndex == state.enemies[i].animFrames-1)
            {
                state.enemies[i].animIndices = state.enemies[i].animUpAtk;
                state.enemies[i].animFrames = 10;
                state.enemies[i].animIndex = 0;
            }
        }

        else if (state.enemies[i].animIndices == state.enemies[i].animUpAtk)
        {
            state.enemies[i].movement.x = 0.25f;
            if (state.enemies[i].animIndex == state.enemies[i].animFrames-1)
            {
                state.enemies[i].animIndices = state.enemies[i].animRight;
                state.enemies[i].animFrames = 5;
            }
        }

        if (state.enemies[i].position.x >= 5.0f)
        {
            youLose = true;
        }

        if (fabs(state.player->position.x - state.enemies[i].position.x) < .4f)//If we're matching the enemy x
        {
            if (fabs(state.player->position.y - state.enemies[i].position.y) < .4f)//...and the y
            {
                if (!state.enemies[i].dead)//...and their alive
                {
                    if (state.enemies[i].animIndices == state.enemies[i].animUpAtk || state.enemies[i].animIndices == state.enemies[i].animRightAtk)
                    {//And they're in an attack phase!
                        youLose = true;
                    }
                }
            }
        }
    }
    state.player->Update(deltaTime);
    state.enemies[0].Update(deltaTime);
    state.enemies[1].Update(deltaTime);
    state.enemies[2].Update(deltaTime);

    if (state.enemies[0].dead)
    {
        if (state.enemies[1].dead)
        {
            if (state.enemies[2].dead)
            {
                youWin = true;
            }
        }
    }
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (startScreen)
    {
        DrawText(&program, font, "Arrow keys: Move", .3, .02, glm::vec3(-4.0f, 2.5f, 0.0f));
        DrawText(&program, font, "Space : Throw Snowball", .3, .02, glm::vec3(-4.0f, 2.0f, 0.0f)); 
        DrawText(&program, font, "Press Space to Start", .3, .02, glm::vec3(-4.0f, 1.5f, 0.0f));
        DrawText(&program, font, "Don't let them across!", .3, .02, glm::vec3(-4.0f, 0.5f, 0.0f));
        DrawText(&program, font, "If you get hit, you lose!", .3, .02, glm::vec3(-4.0f, 0.0f, 0.0f));
        DrawText(&program, font, "Don't let them pass!", .3, .02, glm::vec3(-4.0f, -0.5f, 0.0f));
    }
    else if (youLose)
    {
        DrawText(&program, font, "RIP :( You Lose!", .3, .02, glm::vec3(-2.0f, 0.0f, 0.0f));
    }
    else if (youWin)
    {
        DrawText(&program, font, "You Win!", .3, .02, glm::vec3(-2.0f, 0.0f, 0.0f));
    }
    else
    {
        program.SetModelMatrix(state.player->modelMatrix);
        for (int i = 0; i < 3; i++)
        {
            state.enemies[i].Render(&program);
        }

        state.player->Render(&program);

        if (state.shot->attackInPlace == true)
        {
            float vertices[] = { -0.15f, -0.15f, 0.15f, -0.15f, 0.15f, 0.15f, -0.15f, -0.15f, 0.15f, 0.15f, -0.15f, 0.15f };
            float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };


            program.SetModelMatrix(state.shot->modelMatrix);
            program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

            glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
            glEnableVertexAttribArray(program.positionAttribute);

            glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
            glEnableVertexAttribArray(program.texCoordAttribute);


            glBindTexture(GL_TEXTURE_2D, state.shot->textureID);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableVertexAttribArray(program.positionAttribute);
            glDisableVertexAttribArray(program.texCoordAttribute);



        }
    }
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
