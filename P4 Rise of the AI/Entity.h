
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