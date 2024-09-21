#include <memory>
#include "glad.h"
class Disk;
using DiskPtr = std::shared_ptr<Disk>;

#ifndef DISK_H
#define DISK_H

#include "shape.h"

class Disk : public Shape
{
  unsigned int m_vao;

protected:
  Disk();

public:
  static DiskPtr Make();
  virtual ~Disk();
  virtual void Draw();

private:
  int indexLocation; // Armazena o location do uniform circleIndex
  GLuint m_vaos[5];  // Array de VAOs para os 5 discos
  GLuint m_vbos[5];  // Array de VBOs para os 5 discos
  GLuint m_ebos[5];  // Array de EBOs para os 5 discos
};
#endif