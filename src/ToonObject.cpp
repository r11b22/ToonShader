//
// Created by joost on 6/13/26.
//

#include "ToonObject.h"

ToonObject::ToonObject(const std::string &name, const std::shared_ptr<Mesh> &mesh, const std::shared_ptr<Material> &material)
    : TransformableObject(name), MeshObject(name, mesh, material)
{

}

std::vector<RenderCommand> ToonObject::getRenderCommands() {
    std::vector<RenderCommand> defaultCommands = MeshObject::getRenderCommands();

    RenderCommand outlineCommand;

    outlineCommand.renderable = getMesh();
    outlineCommand.material = getMaterial();
    outlineCommand.shaderName = "outlineShader";
    outlineCommand.uniforms.push_back({"uModelMatrix", getTransformationMatrix()});
    outlineCommand.uniforms.push_back({"uOutlineThickness", 0.005f});

    outlineCommand.state.cullMode = CullMode::Front;

    defaultCommands.push_back(outlineCommand);
    return defaultCommands;
}
