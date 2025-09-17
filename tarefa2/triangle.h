#include <memory>
#include <vector>
class Triangle;
using TrianglePtr = std::shared_ptr<Triangle>; 

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glm/glm.hpp>
#include "shape.h"

class Triangle : public Shape {
  unsigned int m_vao;
protected:
  Triangle ();
  Triangle(std::vector<glm::vec2> coord);

public:
  static TrianglePtr Make (std::vector<glm::vec2> coord);
  virtual ~Triangle ();
  virtual void Draw ();
};
#endif