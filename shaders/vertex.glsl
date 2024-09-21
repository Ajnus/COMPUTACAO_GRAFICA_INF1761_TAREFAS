#version 410

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; // Cor do vértice
out vec4 vertexColor;

layout(location = 0) in vec4 coord;
uniform mat4 M;

uniform int circleIndex; // Uniform que será atualizado em cada iteração

void main()
{
    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    //vertexColor = aColor; // vec4(1.0, 0.0, 0.0, 1.0);

    // Para usar cores diferentes para cada posição de vértice
    if (aPos.x == -0.5f && aPos.y == -0.5f) {
        //vertexColor = vec4(137.0f/255.0f, 250.0f/255.0f, 195.0f/255.0f, 1.0);
    } else if (aPos.x == -0.6f && aPos.y == 0.5f) {
        //vertexColor = vec4(165.0f/255.0f, 208.0f/255.0f, 239.0f/255.0f, 1.0);
    } else if (aPos.x == -0.15f && aPos.y == 0.2f) {
        //vertexColor = vec4(231.0f/255.0f, 150.0f/255.0f, 153.0f/255.0f, 1.0);
    } else if (aPos.x == 0.5f && aPos.y == 0.5f) {
        //vertexColor = vec4(215.0f/255.0f, 168.0f/255.0f, 236.0f/255.0f, 1.0);
    } else if (aPos.x == 0.3f && aPos.y == -0.4f) {
        //vertexColor = vec4(244.0f/255.0f, 239.0f/255.0f, 152.0f/255.0f, 1.0);
    }
}
