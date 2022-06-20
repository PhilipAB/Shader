#ifndef MESH_H
#define MESH_H

#include <vector>
#include <CommonTypes.h>
#include <ShaderProgram.h>

class Mesh {

public:
    Mesh(std::vector<Vertex> vertices, std::vector<VertexAttribute> attributes, std::vector<Index> indices);
    ~Mesh();

    void bind(ShaderProgram *shader);
    void unbind();
    void render(ShaderProgram *shader);

private:
    GLuint vaoID, vboID, iboID;
    GLsizei numIndices;
    ShaderProgram* m_shader;
};

#endif //MESH_H