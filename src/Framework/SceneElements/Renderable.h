#include <vector>
#include "Mesh.h"
#include "Transform.h"
#include "ShaderProgram.h"
#include <glm/gtx/string_cast.hpp>

class Renderable : public Transform {
public:
    Renderable();
    Renderable(std::vector<Mesh*> meshes);
    virtual ~Renderable();
    void addMesh(Mesh *mesh);
    void render(ShaderProgram * shader);
private:
    std::vector<Mesh*> meshes;

};