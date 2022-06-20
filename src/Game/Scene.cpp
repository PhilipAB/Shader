#include "Scene.h"
#include <AssetManager.h>
#include "OBJLoader.h"

Scene::Scene(GameWindow *window) :
        m_window(window) {
    assert(window != nullptr);
}

Scene::~Scene() {}

bool Scene::init() {
    try {
        dtSum = 0.0f;
        renderableSphere1 = new Renderable();
        renderableSphere2 = new Renderable();
        renderableSphere3 = new Renderable();
        renderableGround = new Renderable();
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl",
                                                                              "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");

        objResSphere = OBJLoader::loadOBJ("assets/models/sphere.obj", false, false);

        std::vector<OBJMesh> meshes = objResSphere.objects[0].meshes;

        for (OBJMesh &meshObj : meshes) {
            OBJLoader::reverseWinding(meshObj);
            renderableSphere1->addMesh(new Mesh(meshObj.vertices, meshObj.atts, meshObj.indices));
            renderableSphere2->addMesh(new Mesh(meshObj.vertices, meshObj.atts, meshObj.indices));
            renderableSphere3->addMesh(new Mesh(meshObj.vertices, meshObj.atts, meshObj.indices));
        }

        objResGround = OBJLoader::loadOBJ("assets/models/ground.obj", false, false);

        std::vector<OBJMesh> meshesGround = objResGround.objects[0].meshes;

        for (OBJMesh &meshObj : meshesGround) {
            renderableGround->addMesh(new Mesh(meshObj.vertices, meshObj.atts, meshObj.indices));
        }

        renderableSphere1->scale(glm::vec3(0.5f, 0.5f, 0.5f));
        renderableGround->rotate(glm::vec3(90, 0, 0));
        renderableGround->scale(glm::vec3(0.5f, 0.5f, 0.5f));

        renderableSphere2->setParent(renderableSphere1);
        renderableSphere2->scale(glm::vec3(0.5));
        renderableSphere2->translate(glm::vec3(1,0.5,0));
        renderableSphere3->setParent(renderableSphere1);
        renderableSphere3->scale(glm::vec3(0.5));
        renderableSphere3->translate(glm::vec3(-1,0.5,0));



//        std::vector<Vertex> verticesNew{Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
//                                        Vertex{glm::vec3(0.5f, -0.5f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
//                                        Vertex{glm::vec3(0.5f, 0.5f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
//                                        Vertex{glm::vec3(0.0f, 1.0f,0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
//                                        Vertex{glm::vec3(-0.5f, 0.5f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}};
//
//        std::vector<VertexAttribute> verticesAttributes{VertexAttribute{3, GL_FLOAT, sizeof(Vertex), 0},
//                                                        VertexAttribute{3, GL_FLOAT, sizeof(Vertex), sizeof(verticesNew[0].position)}};
//
//        std::vector<Index> indicesNew{0, 1, 2,
//                                      0, 2, 4,
//                                      4, 2, 3};
//
//        m_mesh = new Mesh(verticesNew, verticesAttributes, indicesNew);
//        renderable->addMesh(m_mesh);

        //initial opengl state
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        std::cout << "Scene initialization done\n";

        return true;
    }
    catch (std::exception &ex) {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::shutdown() {

}

void Scene::render(float dt) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader->use();
    dtSum += dt*0.1f;

    if(dtSum >= 1) {
        dtSum = dtSum - 1;
    }

    float my_floats[4] = {dtSum, 1-dtSum, 0.5, 1.0f};
    float inverted[4] = { 1 - my_floats[0], 1 - my_floats[1], 1 - my_floats[2], 1 - my_floats[3]};
    GLint my_location = glGetUniformLocation(m_shader->prog, "uniformcolor");
    glProgramUniform4fv(m_shader->prog, my_location, 1, my_floats);
    renderableSphere1->render(m_shader);
    glProgramUniform4fv(m_shader->prog, my_location, 1, inverted);
    renderableSphere2->render(m_shader);
    renderableSphere3->render(m_shader);
    my_floats[0] = 1.0f;
    my_floats[1] = 0.5f;
    glProgramUniform4fv(m_shader->prog, my_location, 1, my_floats);
    renderableGround->render(m_shader);
}

void Scene::update(float dt) {
    if (m_window->getInput().getKeyState(Key::W) == KeyState::Pressed) {
        // Move forward
        renderableSphere1->translate(glm::vec3(0, dt * 0.5, 0));
    } else if (m_window->getInput().getKeyState(Key::A) == KeyState::Pressed) {
        // Move left
        renderableSphere1->translate(glm::vec3(dt * -0.5, 0, 0));
    } else if (m_window->getInput().getKeyState(Key::S) == KeyState::Pressed) {
        // Move backwards
        renderableSphere1->translate(glm::vec3(0, dt * -0.5, 0));
    } else if (m_window->getInput().getKeyState(Key::D) == KeyState::Pressed) {
        // Move right
        renderableSphere1->translate(glm::vec3(dt * 0.5, 0, 0));
    } else if (m_window->getInput().getKeyState(Key::Q) == KeyState::Pressed) {
        // Rotate anticlockwise
        renderableSphere1->rotate(glm::angleAxis(glm::radians(dt * 30.f), glm::vec3(0, 0, 1)));
    } else if (m_window->getInput().getKeyState(Key::E) == KeyState::Pressed) {
        // Rotate clockwise
        renderableSphere1->rotate(glm::angleAxis(glm::radians(dt * -30.f), glm::vec3(0, 0, 1)));
    } else if (m_window->getInput().getKeyState(Key::R) == KeyState::Pressed) {
        // Scale Up
        renderableSphere1->scale(glm::vec3((dt * 0.2) + 1));
    } else if (m_window->getInput().getKeyState(Key::F) == KeyState::Pressed) {
        // Scale Up
        renderableSphere1->scale(glm::vec3(1 - (dt * 0.2)));
    }
}

GameWindow *Scene::getWindow() {
    return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier) {

}

void Scene::onMouseMove(MousePosition mouseposition) {

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier) {

}

void Scene::onMouseScroll(double xscroll, double yscroll) {

}

void Scene::onFrameBufferResize(int width, int height) {

}