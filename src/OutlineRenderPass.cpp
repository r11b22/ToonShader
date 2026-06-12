//
// Created by joost on 6/10/26.
//

#include "OutlineRenderPass.h"

#include <iostream>

#include "FileReader.h"

OutlineRenderPass::OutlineRenderPass()
{

}

std::optional<std::string> OutlineRenderPass::getCustomShaderName() {
    return "outlineShader";
}

void OutlineRenderPass::drawObject(std::shared_ptr<IDrawable> drawable, ShaderProgram &currentProgram) {
    currentProgram.setUniformFloat("uOutlineThickness", 0.01f);

    drawable->draw(currentProgram);
}

void OutlineRenderPass::setupState() {
    // The stencil and depth tests are already enabled by the engine/previous pass,
    // we just tweak their behavior:
    glCullFace(GL_FRONT);      // Draw ONLY back-faces for the outline
    glDepthMask(GL_FALSE);     // Outlines don't write to depth
    glDepthFunc(GL_LEQUAL);    // Outlines can sit on the exact same depth plane

    glStencilMask(0x00);       // Lock stencil (Read-only)
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Only draw where stencil is exactly 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void OutlineRenderPass::resetState() {
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glDisable(GL_STENCIL_TEST); // Turn off stencil when completely done with the effect
    glStencilMask(0xFF);        // Clear the write lock
}
