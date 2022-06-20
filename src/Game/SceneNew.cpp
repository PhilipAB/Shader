#include "Scene.h"
#include <AssetManager.h>
#include "Renderable.h"
#include "Mesh.h"

Scene::Scene(GameWindow *window) :
        m_window(window) {
    assert(window != nullptr);
}

Scene::~Scene() {}

auto renderable = new Renderable();

bool Scene::init() {
    try {
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl",
                                                                              "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");

        std::vector<Vertex> verticesNew{Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
                                        Vertex{glm::vec3(0.5f, -0.5f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
                                        Vertex{glm::vec3(0.5f, 0.5f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
                                        Vertex{glm::vec3(0.0f, 1.0f,0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
                                        Vertex{glm::vec3(-0.5f, 0.5f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}};

        std::vector<VertexAttribute> verticesAttributes{VertexAttribute{2, GL_FLOAT, 5 * sizeof(float), 0},
                                                        VertexAttribute{3, GL_FLOAT, 5 * sizeof(float), (2 * sizeof(float))}};

        std::vector<Index> indicesNew{0, 1, 2,
                                      0, 2, 4,
                                      4, 2, 3};

        Mesh* newMesh = new Mesh(verticesNew, verticesAttributes, indicesNew);
        renderable->addMesh(newMesh);

        //initial opengl state
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
    glClear(GL_COLOR_BUFFER_BIT);
    renderable->render(m_shader);
}

void Scene::update(float dt) {

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