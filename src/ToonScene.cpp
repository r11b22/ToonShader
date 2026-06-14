//
// Created by joost on 6/8/26.
//

#include "ToonScene.h"

#include "FileReader.h"
#include "ToonObject.h"
#include "Defaults/Camera/FirstPersonCamera.h"
#include "Renderer/Renderer.h"
#include "Utilities/Random.h"


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

    for (int i = 0; i < 5; i++) {
        auto tiger = std::make_shared<ToonObject>("tiger", tigerMesh, tigerMaterial);
        addObject(tiger);
        tiger->setPosition(glm::vec3{getRandomFloat(-5.0f, 5.0f), getRandomFloat(-5.0f, 5.0f), getRandomFloat(-5.0f, 5.0f)});
        tiger->setShader("toonShader");
        mTigers.push_back(tiger);


        if (i == 0) {
            glm::vec3 diff = tiger->getPosition() - camera->getPosition();
            camera->lookAt(glm::normalize(diff));
        }
    }


    std::shared_ptr<AmbientLight> ambientLight = std::make_shared<AmbientLight>("ambient light", glm::vec3{0.5f, 0.5f, 0.5f});
    addObject(ambientLight);
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
