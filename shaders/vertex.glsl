#version 410

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
out vec4 vertexColor;
uniform int circleIndex; // Uniform que será atualizado em cada iteração

void main()
{
    gl_Position = vec4(aPos, 1.0);

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
