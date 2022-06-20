#include "Scene.h"
#include <AssetManager.h>

Scene::Scene(GameWindow *window) :
        m_window(window) {
    assert(window != nullptr);
}

Scene::~Scene() {}

bool Scene::init() {
    try {
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl",
                                                                              "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");

        /*
         * ************
         * Place your code here!
         *
         * ************
         */

        // vertex data //
        float vertices[25] = {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
                              0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
                              0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                              0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                              -0.5f, 0.5f, 0.0f, 1.0f, 0.0f}; // stores the data of your vertices

        uint32_t numVertices = 5;

        // indices //
        uint32_t indices[9] = {0, 1, 2,
                               0, 2, 4,
                               4, 2, 3};

        uint32_t numIndices = 9;

        // vertex data Initialien //
        float verticesInit[45] = {-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
                                  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
                                  -0.4f, 0.5f, 0.0f, 0.0f, 1.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                                  -0.25f, 0.9f, 0.0f, 0.0f, 1.0f,
                                  0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
                                  -0.1f, 0.75f, 0.0f, 0.0f, 1.0f,
                                  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                                  -0.25f, 0.6f, 0.0f, 0.0f, 1.0f}; // stores the data of your vertices

        uint32_t numVerticesInit = 9;

        // indices //
        uint32_t indicesInit[12] = {2, 1, 0,
                                    4, 3, 1,
                                    6, 5, 3,
                                    8, 7, 5};

        uint32_t numIndicesInit = 12;

        // setup VAO //
        // create and activate vertex array object //
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // setup VBO //
        // create and activate vertex buffer object //
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        // upload data //
        glBufferData(GL_ARRAY_BUFFER, numVerticesInit * sizeof(verticesInit), &verticesInit, GL_STATIC_DRAW);
        // describe data layout and activate it //
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

        // setup IBO //
        glGenBuffers(1, &iboID); //only works after glGenVertexArrays();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicesInit*sizeof(indicesInit), indicesInit, GL_STATIC_DRAW);

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
    m_shader->use();

    // activate VAO //
    // render call //
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); GLERR
    // good programmers should reset //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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