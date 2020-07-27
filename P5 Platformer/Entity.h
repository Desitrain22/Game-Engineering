#pragma once
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
#include "Map.h"

enum EntityType{PLAYER, PLATFORM, COLLECTABLE, ENEMY};

class Entity {
public:

    EntityType type;

    glm::vec3 position;
    glm::vec3 movement;
    float speed;
    float height = 1.0f;
    float width = 1.0f;

    bool isActive = true;
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;

    bool token = false;

    bool jump = false;

    int objectCount;

    glm::vec3 acceleration;
    glm::vec3 velocity;

    GLuint textureID;

    glm::mat4 modelMatrix;

    int* animRight = NULL;
    int* animLeft = NULL;
    int* animUp = NULL;
    int* animDown = NULL;

    int* animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;

    Entity(EntityType type);
    Entity();

    void Update(float deltaTime, Entity* player, Entity* objects, int objectCount, Map* map);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);
    bool CheckCollision(Entity* other);
    void CheckCollisionsY(Entity* objects, int objectCount);
    void CheckCollisionsX(Entity* objects, int objectCount);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsY(Map* map);

};
/*
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
class Entity {
public:
    glm::vec3 position;
    glm::vec3 movement;
    float speed = 1; 
    int* animRight = NULL;
    int* animRightAtk = NULL;

    int* animDown = NULL;
    int* animDownAtk = NULL;

    int* animUp = NULL;
    int* animUpAtk = NULL;

    int* animIndices = NULL;

    int animFrames  = NULL;
    int animIndex = NULL;
    float animTime = NULL;

    int rows = 0;
    int cols = 0;
    float timer = 0;

    bool attackInPlace = false;
    bool dead = false;
    GLuint textureID;

    glm::mat4 modelMatrix;
    Entity();

    void Update(float deltaTime);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program);
};
*/