//
// Created by joost on 6/13/26.
//

#ifndef TOONSHADER_TOONOBJECT_H
#define TOONSHADER_TOONOBJECT_H
#include "Defaults/Objects/Drawables/MeshObject.h"

class ToonObject : public MeshObject {
private:
    float mOutlineWidth;
public:
    ToonObject(const std::string& name, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, float outlineWidth = 0.2f);
    ~ToonObject() = default;

    std::vector<RenderCommand> getRenderCommands() override;
private:
};
#endif //TOONSHADER_TOONOBJECT_H
