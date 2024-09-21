#include "triangle.h"
#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "error.h"

TrianglePtr Triangle::Make ()
{
  return TrianglePtr(new Triangle());
}

Triangle::Triangle ()
{
  float coord[] = {
   -0.5f,-0.5f, 
    0.5f,-0.5f,
    0.0f, 0.5f,
  };
  unsigned char color[] = {
    255,0,0,
    0,255,0,
    0,0,255
  };
  unsigned int index[] = {0,1,2};

  // create VAO
  glGenVertexArrays(1,&m_vao);
  Error::Check("After glGenVertexArrays");
  glBindVertexArray(m_vao);
  Error::Check("After glBindVertexArray");


  // create coord buffer
  GLuint id[3];
  glGenBuffers(3,id);
  Error::Check("After glGenBuffers");


  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  Error::Check("After glBindBuffer");
  glBufferData(GL_ARRAY_BUFFER,2*3*sizeof(float),(void*)coord,GL_STATIC_DRAW);
  Error::Check("After glBufferData");
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  Error::Check("After glVertexAttribPointer");
  glEnableVertexAttribArray(0);
  Error::Check("After glEnableVertexAttribArray");
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  Error::Check("After glBindBuffer");
  glBufferData(GL_ARRAY_BUFFER,3*3*sizeof(unsigned char),(void*)color,GL_STATIC_DRAW);
  Error::Check("After glBufferData");
  glVertexAttribPointer(1,3,GL_UNSIGNED_BYTE,GL_TRUE,0,0);  // color
  Error::Check("After glVertexAttribPointer");
  glEnableVertexAttribArray(1);
  Error::Check("After glEnableVertexAttribArray");
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id[2]);
  Error::Check("After glBindBuffer");
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,3*sizeof(GLuint),(void*)index ,GL_STATIC_DRAW);
  Error::Check("After glBufferData");
}

Triangle::~Triangle () 
{
  glDeleteVertexArrays(1,&m_vao);
  Error::Check("After glDeleteVertexArrays");
}

void Triangle::Draw ()
{
  glBindVertexArray(m_vao);
  Error::Check("After glBindVertexArray");
  glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);
  Error::Check("After glDrawElements");
  //glDrawArrays(GL_TRIANGLES,0,3);
}