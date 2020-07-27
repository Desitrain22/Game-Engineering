#include "Home.h"
#define Home_WIDTH 14
#define Home_HEIGHT 8

#define Home_ENEMY_COUNT 0

unsigned int Home_data[] =
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
void Home::Initialize() {


    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet.png");
    state.map = new Map(Home_WIDTH, Home_HEIGHT, Home_data, mapTextureID, 1.0f, 14, 7);
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
void Home::Update(float deltaTime) {
    //state.player->Update(deltaTime, state.player, state.enemies, Home_ENEMY_COUNT, state.map);
}
void Home::Render(ShaderProgram* program) {
    //state.map->Render(program);
    //state.player->Render(program);
    Util::DrawText(program, Util::LoadTexture("font2.png"), "Portal, but without portals", .25f, .0002f, glm::vec3(-3.65, 2, 0));
    Util::DrawText(program, Util::LoadTexture("font2.png"), "Get the key; escape the room", .25f, .0002f, glm::vec3(-3.65, 1.5, 0));
    Util::DrawText(program, Util::LoadTexture("font2.png"), "Start: Enter", .15f, .0002f, glm::vec3(-3.65, 1, 0));
}