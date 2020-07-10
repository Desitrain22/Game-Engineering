#include "Entity.h"
Entity::Entity()
{
    position = glm::vec3(0);
    speed = 1;

    modelMatrix = glm::mat4(1.0f);
}

void Entity::Update(float deltaTime)
{

	if (!dead)
	{
		position += movement * speed * deltaTime;
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
	}
	if (dead)
	{
		animIndex = 6;
	}
	else if ((glm::length(movement) != 0) || attackInPlace)
	{
		animTime += deltaTime;
		if (animTime >= 0.15f)
		{
			animTime = 0.0f;
			animIndex++;
			if (animIndex >= animFrames)
			{
				if (dead)
				{
					animIndex = animFrames;
				}
				animIndex = 0;
			}
		}
	}
	else
	{
		animIndex = 0;
	}
}

void Entity::Render(ShaderProgram* program) {
    program->SetModelMatrix(modelMatrix);

    if (animIndices != NULL)
    {
        DrawSpriteFromTextureAtlas(program);
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

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram* program)
{
    float u = (float)(animIndices[animIndex] % cols) / (float)cols;
    float v = (float)(animIndices[animIndex] / cols) / (float)rows;

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
}