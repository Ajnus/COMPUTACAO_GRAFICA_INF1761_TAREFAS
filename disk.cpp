#include "disk.h"
#include "triangle.h"
#include <iostream>
#include "shader.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include "error.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "polygon.h"

#define PI 3.14159265359f
static ShaderPtr shd;

DiskPtr Disk::Make()
{
    return DiskPtr(new Disk());
}

Disk::Disk()
{
    int n = 100;         // Número de triângulos (suavidade do círculo)
    float radius = 0.1f; // Raio do círculo

    float xy[][2] = {
        -0.5f,
        -0.5f,
        -0.6f,
        0.5f,
        -0.15f,
        0.2f,
        0.5f,
        0.5f,
        0.3f,
        -0.4f,
    };

    float cx = 0.0f, cy = 0.0f;

    // Arrays para armazenar VAOs, VBOs, e EBOs para os discos
    glGenVertexArrays(5, m_vaos);
    glGenBuffers(5, m_vbos);
    glGenBuffers(5, m_ebos);

    for (int j = 0; j < 5; j++)
    {
        std::cout << "j: " << j << "\n";
        cx = xy[j][0];
        cy = xy[j][1];

        std::cout << "cx: " << cx << "\n";
        std::cout << "cy: " << cy << "\n";

        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        // Adicionar o centro do círculo
        vertices.push_back(cx);
        vertices.push_back(cy);

        // Adicionar vértices ao redor do círculo
        for (int i = 0; i <= n; i++)
        {
            // std::cout << "i: " << i << "\n";
            float theta = (2.0f * PI * i) / n;
            float x = cx + radius * cos(theta);
            float y = cy + radius * sin(theta);
            vertices.push_back(x);
            vertices.push_back(y);

            // Índices para formar triângulos
            if (i < n)
            {
                indices.push_back(0); // Sempre o centro do círculo
                indices.push_back(i + 1);
                indices.push_back(i + 2);
            }
        }

        // Corrigir o último índice para voltar ao primeiro ponto
        indices[indices.size() - 1] = 1;

        // Bind VAO para este disco
        glBindVertexArray(m_vaos[j]);
        Error::Check("After glBindVertexArray(m_vaos[j])");

        // Bind VBO and send vertex data
        glBindBuffer(GL_ARRAY_BUFFER, m_vbos[j]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        Error::Check("After glBufferData (VBO)");

        // Bind EBO and send index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[j]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        Error::Check("After glBufferData (EBO)");

        // Enable vertex attributes
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0); // Coord
        glEnableVertexAttribArray(0);
        Error::Check("After glVertexAttribPointer and glEnableVertexAttribArray");

        glBindVertexArray(0); // Unbind VAO
    }
}

Disk::~Disk()
{
    glDeleteVertexArrays(5, m_vaos);
    Error::Check("After glDeleteVertexArrays(5, m_vaos)");
    glDeleteBuffers(5, m_vbos);
    Error::Check("After glDeleteBuffers(5, m_vbos)");
    glDeleteBuffers(5, m_ebos);
    Error::Check("After glDeleteBuffers(5, m_ebos)");
}

void Disk::Draw()
{
    // std::cout << "disk->Draw()";

    for (int i = 0; i < 5; i++)
    {
        glUniform1i(indexLocation, i); // Atualiza a posição do centro do (novo) círculo
        glBindVertexArray(m_vaos[i]);
        glDrawElements(GL_TRIANGLES, 300, GL_UNSIGNED_INT, 0); // 300 = 3 * número de triângulos (n)
    }
}