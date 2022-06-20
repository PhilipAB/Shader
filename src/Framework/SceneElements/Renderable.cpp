#include "Renderable.h"

Renderable::Renderable() {

}

Renderable::Renderable(std::vector<Mesh *> meshes_in) {
    meshes = std::move(meshes_in);
}

Renderable::~Renderable() {

}

void Renderable::addMesh(Mesh *mesh) {
    meshes.push_back(mesh);
}

void Renderable::render(ShaderProgram * shader) {
    glm::mat4 modelMatrix = getTransformMatrix();
    Transform* parent = this->getParent();

    while(parent != nullptr){
        modelMatrix = parent->getTransformMatrix() * modelMatrix;
        parent = parent->getParent();
    }
    shader->setUniform("modelmatrix", modelMatrix, false);

    for (Mesh *mesh : meshes) {
        mesh->render(shader);
    }
}