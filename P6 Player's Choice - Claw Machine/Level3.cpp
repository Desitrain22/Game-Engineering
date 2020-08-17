#include "Level3.h"
#define Level3_WIDTH 12
#define Level3_HEIGHT 12

#define Level3_ENEMY_COUNT 1

unsigned int Level3_data[] =
{
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 10, 10, 10, 255, 255, 255, 255, 255, 10, 10, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 10, 10, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 10, 10, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 255, 255, 255, 255, 10, 10, 255, 255, 10, 10, 10,
    10, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
};



void Level3::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet.png");
    state.map = new Map(Level3_WIDTH, Level3_HEIGHT, Level3_data, mapTextureID, 1.0f, 16, 16);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->position = glm::vec3(2, -1, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, 3.0f, 0);
    state.player->speed = 3.0f;
    state.player->textureID = Util::LoadTexture("crane.png");
    state.player->animIndices = NULL;

    state.enemies = new Entity(ENEMY);

    state.enemies->animIndices = new int[9]{ 26,27,28,29,30,31,32,33,34};

    state.enemies->animFrames = 9;
    state.enemies->animIndex = 0;
    state.enemies->animTime = 0;
    state.enemies->animCols = 13;
    state.enemies->animRows = 8;

    state.enemies->position = glm::vec3(1, -10, 0);
    state.enemies->movement = glm::vec3(0);
    state.enemies->acceleration = glm::vec3(0, -9.8f, 0);
    state.enemies->velocity = glm::vec3(0.5f, 0, 0);
    state.enemies->textureID = Util::LoadTexture("astronaut3.png");


    state.door = new Entity(DOOR);
    state.door->textureID = Util::LoadTexture("basket.png");
    state.door->position = glm::vec3(8.99f, -2.98f, 0);
    state.door->velocity = glm::vec3(0);
    state.door->acceleration = glm::vec3(0);
    state.door->movement = glm::vec3(0);



    GLuint objectsTexture = Util::LoadTexture("spinningcoinspritesheet.png");

    state.objects = new Entity[5];

    for (int i = 0; i < 5; i++)
    {
        state.objects[i] = Entity(COLLECTABLE);
        state.objects[i].textureID = objectsTexture;
        state.objects[i].animFrames = 8;
        state.objects[i].animIndex = 0;
        state.objects[i].animTime = 0;
        state.objects[i].animCols = 8;
        state.objects[i].animRows = 1;
        state.objects[i].movement = glm::vec3(0);
        state.objects[i].velocity = glm::vec3(0);
        state.objects[i].animIndices = new int[8]{ 0,1,2,3,4,5,6,7 };
    }

    state.objects[0].position = glm::vec3(6, -7, 0);
    state.objects[1].position = glm::vec3(1, -7, 0);
    state.objects[2].position = glm::vec3(2, -9, 0);
    state.objects[3].position = glm::vec3(9, -4, 0);
    state.objects[4].position = glm::vec3(10, -10, 0);

}

void Level3::Update(float deltaTime) {
    bool done = true;
   
    state.time -= deltaTime;


    state.player->Update(deltaTime, state.player, state.enemies, 1, state.map);
    state.enemies->Update(deltaTime, state.enemies, state.player, 1, state.map);

    for (int i = 0; i < 5; i++)
    {
        state.objects[i].Update(deltaTime, state.player, state.enemies, 1, state.map);

        if (state.player->CheckCollision(&state.objects[i]))
        {
            if (state.objects[i].isActive)
            {
                if (state.objects[i].velocity.y >= -2.0f && !(state.player->token))
                {
                    state.objects[i].token = true;
                    state.player->token = true;
                }
            }
        }

        if (state.objects[i].isActive)
        {
            done = false;
        }

        if (state.objects[i].CheckCollision(state.door))
        {
            state.objects[i].isActive = false;
        }
    }

    if (done)
    {
        state.nextScene = 5;
    }
    state.door->Update(deltaTime, state.enemies, state.player, 1, state.map);
}
void Level3::Render(ShaderProgram* program) {

    state.map->Render(program);
    state.player->Render(program);
    state.enemies->Render(program);
    state.door->Render(program);
    for (int j = 0; j < 5; j++)
    {
        state.objects[j].Render(program);
    }
    
    Util::DrawText(program, textfont, "Time: " + std::to_string(state.time), .15f, .0002f, glm::vec3(state.player->position.x - 3.5, state.player->position.y + 3.5, 0));

}