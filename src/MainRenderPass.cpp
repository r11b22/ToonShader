//
// Created by joost on 6/10/26.
//

#include "MainRenderPass.h"

void MainRenderPass::setupState() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE); // CRITICAL: Culling must be enabled for the front-face trick to work!
    glCullFace(GL_BACK);    // Normal objects render back-faces culled

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void MainRenderPass::resetState() {
    glDepthMask(GL_TRUE);
    glStencilMask(0xFF);
}
