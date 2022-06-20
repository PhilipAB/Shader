#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<VertexAttribute> attributes, std::vector<Index> indices) {

    printf("Initializing mesh\n");

    Vertex *verticesArray = vertices.data();
    Index *indicesArray = indices.data();

    // generate and activate VAO //
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    // generate and activate VBO and upload data //
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArray[0]) * vertices.size(), verticesArray, GL_STATIC_DRAW);

    // describe VBO in the VAO //
    for (int i = 0; i < attributes.size(); ++i) {
        VertexAttribute attribute = attributes.at(i);
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attribute.n, attribute.type, false, attribute.stride, (GLvoid *) attribute.offset);
    }

    // generate index data //
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray[0]) * indices.size(), indicesArray, GL_STATIC_DRAW);

    // set the number of indices to draw //
    numIndices = indices.size();

    // unbind everything //
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    printf("Done Initializing mesh\n");
}

Mesh::~Mesh() {}

void Mesh::render(ShaderProgram * shader) {
    shader->use();
    // activate VAO //
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    // render call - drawing //
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
