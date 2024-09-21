#version 410

// uniform vec4 color;
// out vec4 FragColor;
// out vec4 out;
// in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)
// uniform vec3 circleColor; // Variável uniform para a cor do círculo



out vec4 outcolor;
out vec4 FragColor;

uniform int circleIndex; // Índice do círculo
uniform int objectType; // 0 para polígono, 1 para disco


// Função para retornar a cor com base no índice do círculo
vec3 getColor(int index) {
    if (index == 0)
        return vec3(137.0/255.0, 250.0/255.0, 195.0/255.0); // Cor 1
    else if (index == 1)
        return vec3(165.0/255.0, 208.0/255.0, 239.0/255.0); // Cor 2
    else if (index == 2)
        return vec3(231.0/255.0, 150.0/255.0, 153.0/255.0); // Cor 3
    else if (index == 3)
        return vec3(215.0/255.0, 168.0/255.0, 236.0/255.0); // Cor 4
    else if (index == 4)
        return vec3(244.0/255.0, 239.0/255.0, 152.0/255.0); // Cor 5
    else
        return vec3(1.0, 1.0, 1.0); // Branco padrão
}


void main()
{
    //FragColor = vertexColor;
    //outcolor = color;
    //out = color;
    //FragColor = vec4(circleColor, 1.0); // Usando a cor uniform como saída do fragmento

    // Definir a cor de saída usando o índice do círculo

    if (objectType == 0)
    {
        // Cor preta para o polígono
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else if (objectType == 1)
    {
        FragColor = vec4(getColor(circleIndex), 1.0); // Pegando a cor com base no índice
    }
}   