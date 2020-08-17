#include "Scene.h"
class HowToPlay : public Scene {

public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram* program) override;
};
