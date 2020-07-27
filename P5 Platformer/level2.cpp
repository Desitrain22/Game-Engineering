#include "Level2.h"
#define level2_WIDTH 14
#define level2_HEIGHT 8

#define level2_ENEMY_COUNT 0

unsigned int level2_data[] =
{
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 31, 31, 31, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 76, 12, 12, 12, 47, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 31, 12, 12, 12, 31, 12, 3,
    3,  3,  3,  3,  3,  3, 12, 12, 12,  3,  3,  3,  3, 3
};


unsigned int level2_data_ready[] =
{ 3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 31, 31, 31, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 75, 12, 12, 12, 120, 12, 3,
    3, 12, 12, 12, 12, 12, 12, 31, 12, 12, 12, 31, 12, 3,
    3,  3,  3,  3,  3,  3, 12, 12, 12,  3,  3,  3,  3, 3
};

void Level2::Initialize() {


    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet.png");
    state.map = new Map(level2_WIDTH, level2_HEIGHT, level2_data, mapTextureID, 1.0f, 14, 7);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->position = glm::vec3(1, 0, 0);
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



    state.enemies = new Entity(ENEMY);

    state.enemies->animIndices = new int[9]{26,27,28,29,30,31,32,33,34,};

    state.enemies->animFrames = 9;
    state.enemies->animIndex = 0;
    state.enemies->animTime = 0;
    state.enemies->animCols = 13;
    state.enemies->animRows = 8;

    state.enemies->position = glm::vec3(3, -6, 0);
    state.enemies->movement = glm::vec3(0);
    state.enemies->acceleration = glm::vec3(0, -9.8f, 0);
    state.enemies->velocity = glm::vec3(0.5f, 0, 0);
    state.enemies->textureID = Util::LoadTexture("astronaut3.png");




}
void Level2::Update(float deltaTime) {
    if (state.map->mapDone)
    {
        state.map = new Map(level2_WIDTH, level2_HEIGHT, level2_data_ready, Util::LoadTexture("platformPack_tilesheet.png"), 1.0f, 14, 7);
    }

    if (state.map->mapProgress)
    {
        state.nextScene = 3;
    }


    state.player->Update(deltaTime, state.player, state.enemies, level2_ENEMY_COUNT, state.map);
    state.enemies->Update(deltaTime, state.enemies, state.player, level2_ENEMY_COUNT, state.map);
}
void Level2::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);
    Util::DrawText(program, Util::LoadTexture("font2.png"), "Lives: " + std::to_string(state.lives), .15f, .0002f, glm::vec3(state.player->position.x - 3.5, state.player->position.y + 3.5, 0));
    state.enemies->Render(program);
}