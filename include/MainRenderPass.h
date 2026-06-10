//
// Created by joost on 6/10/26.
//

#ifndef TOONSHADER_MAINRENDERPASS_H
#define TOONSHADER_MAINRENDERPASS_H
#include "Renderer/BasicRenderPass.h"

class MainRenderPass : public BasicRenderPass{
private:
public:
    void setupState() override;
    void resetState() override;
private:
};

#endif //TOONSHADER_MAINRENDERPASS_H