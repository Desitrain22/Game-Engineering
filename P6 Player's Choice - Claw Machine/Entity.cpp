#include "Entity.h"

Entity::Entity(EntityType type) : type(type)
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    velocity = glm::vec3(0);
    acceleration = glm::vec3(0);
    speed = 0;

    modelMatrix = glm::mat4(1.0f);
}

Entity::Entity()
{

    position = glm::vec3(0);
    movement = glm::vec3(0);
    velocity = glm::vec3(0);
    acceleration = glm::vec3(0);
    speed = 0;

    modelMatrix = glm::mat4(1.0f);
}

void Entity::CheckCollisionsY(Entity* objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            float ydist = fabs(position.y - object->position.y);
            float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
            if (velocity.y > 0) {
                position.y -= penetrationY;
                velocity.y = 0;
                collidedTop = true;
            }
            else if (velocity.y < 0) {
                position.y += penetrationY;
                velocity.y = 0;
                collidedBottom = true;
            }
        }
    }
}

bool Entity::CheckCollision(Entity* other)
{
    if (isActive == false || other->isActive == false)
    {
        return false;
    } 
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    return (xdist < 0 && ydist < 0);
}

void Entity::CheckCollisionsX(Entity* objects, int objectCount)
{
    for (int i = 0; i < objectCount; i++)
    {
        Entity* object = &objects[i];

        if (CheckCollision(object))
        {
            float xdist = fabs(position.x - object->position.x);
            float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
            if (velocity.x > 0) {
                position.x -= penetrationX;
                velocity.x = 0;
                collidedRight = true;
            }
            else if (velocity.x < 0) {
                position.x += penetrationX;
                velocity.x = 0;
                collidedLeft = true;
            }
        }
    }
}

void Entity::Update(float deltaTime, Entity* player, Entity* objects, int objectCount, Map* map)
{
    if (type == DOOR)
    {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        return;
    }
    /*
    if (type == COLLECTABLE)
    {
        if (animIndices != NULL) {
            animTime += deltaTime;
            if (animTime >= 0.25f)
            {
                animTime = 0.0f;
                animIndex++;
                if (animIndex >= animFrames)
                {
                    animIndex = 0;
                }
            }
        }
        else {
            animIndex = 0;
        }

        if (token)
        {
            position = player->position;
            velocity.y = 0;
        }
        else
        {
            position.y -= -2;
        }
    }
    */
    if (type == ENEMY || type == PLAYER || type == COLLECTABLE)
    {
        collidedTop = false;
        collidedBottom = false;
        collidedLeft = false;
        collidedRight = false;

        /*
        if (jump)
        {
            acceleration.y = 300.0f;
        }
        else
        {
            acceleration.y = -9.8f;
        }
        */


        /*  for (int i = 0; i < platformCount; i++)
          {
              if (CheckCollision(&platforms[i])) return;
          }
          */

        velocity.x = movement.x * speed;
        velocity.y = movement.y * speed;

        if (type == ENEMY)
        {
            if (objects->position.x < position.x)
            {
                velocity = glm::vec3(-0.5f, velocity.y, 0.0f);
            }
            else
            {
                velocity = glm::vec3(0.5f, velocity.y, 0.0f);
            }
        }

        if (type == COLLECTABLE)
        {
            if (token)
            {
                position = player->position;
                velocity = glm::vec3(0);
                acceleration = glm::vec3(0);
            }
            else
            {
                velocity = glm::vec3(0, -5.0f, 0);
            }
        }

        if (type == PLAYER)
        {
            if (velocity.y == 0)
            {
                velocity.y = 3.0f;
            }
        }
        position.y += velocity.y * deltaTime; // Move on Y
        CheckCollisionsY(map);
        //CheckCollisionsY(objects, objectCount); // Fix if needed

        position.x += velocity.x * deltaTime; // Move on X
        CheckCollisionsX(map);
        //CheckCollisionsX(objects, objectCount); // Fix if needed

        

        if (animIndices != NULL) {
            if (glm::length(movement) != 0 || type == ENEMY || type == COLLECTABLE) {
                animTime += deltaTime;

                if (animTime >= 0.25f)
                {
                    animTime = 0.0f;
                    animIndex++;
                    if (animIndex >= animFrames)
                    {
                        animIndex = 0;
                    }
                }
            }
            else {
                animIndex = 0;
            }
        }


        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);

    }

    if (type == PLAYER)
    {
        if (velocity.x <= 0)
        {
            if (player_rotate <= 45)
            {
                player_rotate += 80 * deltaTime;
            }
        }
        if (velocity.x >= 0)
        {
            if (player_rotate >= -45)
            {
                player_rotate -= 80 * deltaTime;
            }
        }
        if (velocity.x == 0)
        {
            if (player_rotate >= 0)
            {
                player_rotate -= 80 * deltaTime;
            }
            else if (player_rotate <= 0)
            {
                player_rotate += 80 * deltaTime;
            }
        }
        modelMatrix = glm::rotate(modelMatrix, glm::radians(player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(player_rotate), glm::vec3(0.0f, 0.0f, 1.0f));


    //jump = false;


}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;

    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;

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

void Entity::Render(ShaderProgram* program)
{
    if (isActive)
    {
        program->SetModelMatrix(modelMatrix);

        if (animIndices != NULL) {
            DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
            return;
        }

        float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
        float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

        glBindTexture(GL_TEXTURE_2D, textureID);

        glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->positionAttribute);

        glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
        glEnableVertexAttribArray(program->texCoordAttribute);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(program->positionAttribute);
        glDisableVertexAttribArray(program->texCoordAttribute);
    }
}

void Entity::CheckCollisionsY(Map* map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);

    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);

    float penetration_x = 0;
    float penetration_y = 0;
    if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
}

void Entity::CheckCollisionsX(Map* map)
{
    // Probes for tiles
    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);

    float penetration_x = 0;
    float penetration_y = 0;
    if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collidedLeft = true;
    }

    if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collidedRight = true;
    }

  
}


