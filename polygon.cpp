#include "polygon.h"
#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "error.h"
#include "triangle.h"

#include <cmath>
#include <vector>
#include <iostream>

#define PI 3.14159265359f

PolygonPtr Polygon::Make(int n, float *xy, unsigned char *rgb, unsigned int *inc)
{
    return PolygonPtr(new Polygon(n, xy, rgb, inc));
}

Polygon::Polygon(int n, float *xy, unsigned char *rgb, unsigned int *inc)
{
    //std::cout << "r: " << rgb[0] << " ";
    //std::cout << "g: " << rgb[1] << " ";
    //std::cout << "b: " << rgb[2] << " ";

    // float x_y = xy

    // create VAO
    glGenVertexArrays(1, &m_vao);
    Error::Check("After glGenVertexArrays");

    glBindVertexArray(m_vao);
    Error::Check("After glBindVertexArray");

    // create coord buffer
    GLuint id[5];
    glGenBuffers(5, id);
    Error::Check("After glGenBuffers");

    glBindBuffer(GL_ARRAY_BUFFER, id[0]);
    glBufferData(GL_ARRAY_BUFFER, 2 * 5 * sizeof(float), (void *)xy, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); // xy
    Error::Check("After glVertexAttribPointer for xy");

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, id[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * 5 * sizeof(unsigned char), (void *)rgb, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0); // color
    Error::Check("After glVertexAttribPointer for rgb");

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(GLuint), (void *)inc, GL_STATIC_DRAW);
    Error::Check("After glBufferData for indices");
}

Polygon::~Polygon()
{
    glDeleteVertexArrays(1, &m_vao);
}

void Polygon::Draw()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_LINE_LOOP, 9, GL_UNSIGNED_INT, 0);
}