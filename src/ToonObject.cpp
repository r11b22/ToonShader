//
// Created by joost on 6/13/26.
//

#include "ToonObject.h"
#include "Renderer/RenderCommand.h"
#include <vector>

ToonObject::ToonObject(const std::string &name, const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Material> &material)
    : TransformableObject(name), MeshObject(name, mesh, material)
{

}

std::vector<RenderCommand> ToonObject::getRenderCommands() {
    std::vector<RenderCommand> defaultCommands = MeshObject::getRenderCommands();

    ClearCommand clearCmd;
    clearCmd.clearColor   = false;
    clearCmd.clearDepth   = false;
    clearCmd.clearStencil = true;
    clearCmd.stencil      = 0; // Clear it back to 0


    StateChangeCommand baseState;
    baseState.state.cullFace    = true;
    baseState.state.cullMode    = CullMode::Back; // Draw front faces normally
    baseState.state.depthTest   = true;
    baseState.state.depthWrite  = true;

    // Stencil Configuration
    baseState.state.stencilTest      = true;
    baseState.state.stencilFunc      = StencilFunc::Always; // Always pass the stencil test
    baseState.state.stencilRef       = 1;                   // We want to write a '1'
    baseState.state.stencilReadMask  = 0xFF;
    baseState.state.stencilWriteMask = 0xFF;                // Enable writing to stencil

    // If stencil passes and depth passes, replace the buffer value with stencilRef (1)
    baseState.state.stencilFailOp    = StencilOp::Keep;
    baseState.state.stencilZFailOp   = StencilOp::Keep;
    baseState.state.stencilZPassOp   = StencilOp::Replace;






    StateChangeCommand outlineState;
    outlineState.state.cullFace    = true;
    outlineState.state.cullMode    = CullMode::Front; // Draw back faces (the inverted hull)
    outlineState.state.depthTest   = true;
    outlineState.state.depthWrite  = false;           // Outlines shouldn't write to the depth buffer

    // Stencil Configuration
    outlineState.state.stencilTest      = true;
    outlineState.state.stencilFunc      = StencilFunc::NotEqual; // ONLY draw where stencil != 1
    outlineState.state.stencilRef       = 1;
    outlineState.state.stencilReadMask  = 0xFF;
    outlineState.state.stencilWriteMask = 0x00;                  // Disable writing to stencil

    outlineState.state.stencilFailOp    = StencilOp::Keep;
    outlineState.state.stencilZFailOp   = StencilOp::Keep;
    outlineState.state.stencilZPassOp   = StencilOp::Keep;

    DrawCommand outlineCommand;

    outlineCommand.renderable = getMesh();
    outlineCommand.material = getMaterial();
    outlineCommand.shaderName = "outlineShader";
    outlineCommand.uniforms.push_back({"uModelMatrix", getTransformationMatrix()});
    outlineCommand.uniforms.push_back({"uOutlineThickness", 0.005f});

    defaultCommands[0] = baseState;
    defaultCommands.insert(defaultCommands.begin() + 1, clearCmd); // clear while writing is enabled
    defaultCommands.push_back(outlineState);
    defaultCommands.push_back(outlineCommand);
    return defaultCommands;
}
