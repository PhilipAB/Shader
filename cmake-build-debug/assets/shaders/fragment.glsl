#version 330 core

//in vec3 colorVS;

//fragment shader output
out vec4 color;

uniform vec4 uniformcolor;

void main(){
    //color = vec4(colorVS.x, colorVS.y, colorVS.z, 1.0);
    color = uniformcolor;
}

