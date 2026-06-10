//
// Created by joost on 6/10/26.
//

#ifndef TOONSHADER_OUTLINERENDERPASS_H
#define TOONSHADER_OUTLINERENDERPASS_H
#include "Renderer/IRenderPass.h"

class OutlineRenderPass : public IRenderPass {
private:
public:
    OutlineRenderPass();
    ~OutlineRenderPass() override = default;

    std::optional<std::string> getCustomShaderName() override;
    void drawObject(std::shared_ptr<IDrawable> drawable, ShaderProgram &currentProgram) override;

    void setupState() override;
    void resetState() override;
private:
};

#endif //TOONSHADER_OUTLINERENDERPASS_H