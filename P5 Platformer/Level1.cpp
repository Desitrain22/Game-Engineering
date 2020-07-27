#include "Level1.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 0

unsigned int level1_data[] =
{
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 47, 12, 12, 12,
    3, 12, 12, 76, 12, 12, 12, 12, 12, 31, 31, 31, 31, 31,
    3, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
    3, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

unsigned int level1_data_ready[] =
{
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    3, 12, 12, 75, 12, 12, 12, 12, 12, 31, 31, 31, 31, 31,
    3, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32,
    3, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};
void Level1::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 14, 7);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->position = glm::vec3(2, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.8f, 0);
    state.player->speed = 3.0f;
    state.player->textureID = Util::LoadTexture("george_0.png");

    state.player->animRight = new int[4]{ 3, 7, 11, 15 };
    state.player->animLeft = new int[4]{ 1, 5, 9, 13 };
    state.player->animUp = new int[4]{ 2, 6, 10, 14 };
    state.player->animDown = new int[4]{ 0, 4, 8, 12 };


    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;




}

void Level1::Update(float deltaTime) {
    
    if (state.map->mapDone)
    {
        state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data_ready, Util::LoadTexture("platformPack_tilesheet.png"), 1.0f, 14, 7);
    }

    if (state.map->mapProgress)
    {
        state.nextScene = 2;
    }
    

    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
}

void Level1::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);


    Util::DrawText(program, Util::LoadTexture("font2.png"), "Lives: " + std::to_string(state.lives), .15f, .0002f, glm::vec3(state.player->position.x - 3.5, state.player->position.y + 3.5, 0));

}