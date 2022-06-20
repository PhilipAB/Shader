#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"
#include "ShaderProgram.h"

class Camera : public Transform {
public:
    Camera(float width, float height, float aperture, float min_dist, float max_dist);
    virtual ~Camera();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void bind(ShaderProgram * shader);
private:
    float camera_width;
    float camera_height;
    float camera_aperture;
    float camera_min_dist;
    float camera_max_dist;
};


#endif //CAMERA_H
