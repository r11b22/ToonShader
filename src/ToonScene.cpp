//
// Created by joost on 6/8/26.
//

#include "ToonScene.h"

#include "FileReader.h"
#include "Lighting/DirectionalLightData.h"
#include "Material/Material.h"
#include "ModelLoader.h"
#include "ToonObject.h"
#include "Defaults/Camera/FirstPersonCamera.h"
#include "Renderer/Renderer.h"
#include "Utilities/Random.h"

#include "Defaults/Objects/Lighting/AmbientLight.h"
#include "Defaults/Objects/Lighting/DirectionalLight.h"
#include "glm/trigonometric.hpp"
#include <memory>


ToonScene::ToonScene() {

}

void ToonScene::onLoad(Renderer &renderer, Window &window) {
    window.setVSYNC(false);

    renderer.setClearBits(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // setup shader
    std::unique_ptr<ShaderProgram> toonShader = std::make_unique<ShaderProgram>();

    toonShader->addShader(FileReader::readFile("Shaders/ToonShader/vertex.glsl").c_str(), GL_VERTEX_SHADER);
    toonShader->addShader(FileReader::readFile("Shaders/ToonShader/fragment.glsl").c_str(), GL_FRAGMENT_SHADER);

    toonShader->link();

    renderer.addShaderProgram("toonShader", std::move(toonShader));


    std::unique_ptr<ShaderProgram> outlineShader = std::make_unique<ShaderProgram>();
    outlineShader->addShader(FileReader::readFile("Shaders/OutlineShader/vertex.glsl").c_str(), GL_VERTEX_SHADER);
    outlineShader->addShader(FileReader::readFile("Shaders/OutlineShader/fragment.glsl").c_str(), GL_FRAGMENT_SHADER);
    outlineShader->link();
    renderer.addShaderProgram("outlineShader", std::move(outlineShader));

    inputManager = new InputManager(window);

    std::shared_ptr<FirstPersonCamera> camera = std::make_shared<FirstPersonCamera>("main camera", *inputManager, window);
    camera->setPosition(glm::vec3{10.0f, 5.0f, 10.0f});
    addObject(camera);

    ModelLoader tigerLoader= {};
    tigerLoader.readFile("Models/Animals/tiger/tiger.gltf");
    tigerLoader.loadTexture("Models/Animals/tiger/Texture_1.png");
    std::shared_ptr<Mesh> tigerMesh = tigerLoader.createMesh();
    std::shared_ptr<Material> tigerMaterial = tigerLoader.createMaterial();
    tigerMaterial->setShininess(64.0f);
    tigerMaterial->setSpecular(0.5f);
   /*for (int i = 0; i < 5; i++) {
        auto tiger = std::make_shared<ToonObject>("tiger", tigerMesh, tigerMaterial);
        addObject(tiger);
        tiger->setPosition(glm::vec3{getRandomFloat(-5.0f, 5.0f), getRandomFloat(-5.0f, 5.0f), getRandomFloat(-5.0f, 5.0f)});
        mTigers.push_back(tiger);


        if (i == 0) {
            glm::vec3 diff = tiger->getPosition() - camera->getPosition();
            camera->lookAt(glm::normalize(diff));
        }
        }*/

    auto tiger = std::make_shared<ToonObject>("tiger", tigerMesh, tigerMaterial, 0.1f);
    addObject(tiger);
    tiger->setPosition({3.5f, 1.1f, 6.0f});
    tiger->rotate(glm::radians(10.0f), {1.0f, 0.0f, 0.0f});
    tiger->rotate(glm::radians(-10.0f), {0.0f, 0.0f, 1.0f});
    glm::vec3 diff = tiger->getPosition() - camera->getPosition();
    camera->lookAt(glm::normalize(diff));

    ModelLoader terrainLoader = {};
    terrainLoader.readFile("Models/Terrain/terrain.gltf");
    terrainLoader.loadTexture("Models/Terrain/Colour_Palette_baseColor.png");

    std::shared_ptr<Mesh> terrainMesh = terrainLoader.createMesh();
    std::shared_ptr<Material> terrainMaterial = terrainLoader.createMaterial();

    terrainMaterial->setShininess(256.0f);
    terrainMaterial->setSpecular(0.2f);

    auto terrain = std::make_shared<ToonObject>("terrain", terrainMesh, terrainMaterial, 0.5f);
    addObject(terrain);


    std::shared_ptr<AmbientLight> ambientLight = std::make_shared<AmbientLight>("ambient light", glm::vec3{0.1f});
    addObject(ambientLight);

    std::shared_ptr<DirectionalLight> directionalLight = std::make_shared<DirectionalLight>("Directional light", glm::vec3{0.5f, 0.5f, 0.2f}, glm::vec3{1.0f});
    addObject(directionalLight);

    renderer.setClearColor({0.05f, 0.1f, 0.3f, 1.0f});
}

void ToonScene::onUpdate(Renderer &renderer, Window &window, float deltaT) {
    // rotate the tigers
    for (const auto& tiger : mTigers ) {
        tiger->rotate(glm::radians(10.0f)*deltaT, glm::vec3{0.0f, 1.0f, 0.0f});
    }
}

ToonScene::~ToonScene() {
    delete inputManager;
}
