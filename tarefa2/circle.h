#include <memory>
#include <vector>
class Circle;
using CirclePtr = std::shared_ptr<Circle>; 

#ifndef Circle_H
#define Circle_H
#include <glm/glm.hpp>
#include "shape.h"

class Circle : public Shape {
  unsigned int m_vao;
protected:
  Circle ();
  Circle(glm::vec2 center, float raio);

public:
  static CirclePtr Make (glm::vec2 center, float raio);
  virtual ~Circle ();
  virtual void Draw ();
};
#endif