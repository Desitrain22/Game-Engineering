#include "YouLose.h"
#define YouLose_WIDTH 14
#define YouLose_HEIGHT 8

#define YouLose_ENEMY_COUNT 0

unsigned int YouLose_data[] =
{
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};
void YouLose::Initialize() {


    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet.png");
    state.map = new Map(YouLose_WIDTH, YouLose_HEIGHT, YouLose_data, mapTextureID, 1.0f, 14, 7);
    // Move over all of the player and enemy code from initialization.
    state.player = new Entity();
    state.player->position = glm::vec3(0, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, 0, 0);
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

    state.player->isActive = false;

    // Move over all of the player and enemy code from initialization.


}
void YouLose::Update(float deltaTime) {
    //state.player->Update(deltaTime, state.player, state.enemies, YouLose_ENEMY_COUNT, state.map);
}
void YouLose::Render(ShaderProgram* program) {
    //state.map->Render(program);
    //state.player->Render(program);
    Util::DrawText(program, Util::LoadTexture("font2.png"), "You Lose!", .5f, .0002f, glm::vec3(-3.65, 2, 0));
    Util::DrawText(program, Util::LoadTexture("font2.png"), "Enter: Home", .5f, .0002f, glm::vec3(-3.65, 1, 0));
}