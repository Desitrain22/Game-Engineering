#include "Level3.h"
#define Level3_WIDTH 14
#define Level3_HEIGHT 8

#define Level3_ENEMY_COUNT 0

unsigned int Level3_data[] =
{
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 34, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 31, 31, 31, 3,
    3, 12, 12, 12, 12, 12, 12, 31, 31, 31, 12, 12, 12, 3,
    3, 12, 75, 12, 31, 31, 31, 12, 12, 12, 12, 12, 12, 3,
    3, 31, 31, 31, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3
};


void Level3::Initialize() {
    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet.png");
    state.map = new Map(Level3_WIDTH, Level3_HEIGHT, Level3_data, mapTextureID, 1.0f, 14, 7);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->position = glm::vec3(0, 0, 0);
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
void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, Level3_ENEMY_COUNT, state.map);
}
void Level3::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);
}