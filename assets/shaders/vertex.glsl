#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

uniform mat4 modelmatrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec3 colorVS;

void main(){
    colorVS = colorRGB;
    gl_Position = modelmatrix * view_matrix * projection_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}
