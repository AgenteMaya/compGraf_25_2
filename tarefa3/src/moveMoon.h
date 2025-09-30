#include <memory>

class MoveMoon;
using MoveMoonPtr = std::shared_ptr<MoveMoon>;

#include "engine.h"
#include "transform.h"

class MoveMoon : public Engine 
{
  TransformPtr m_trf;
protected:
  MoveMoon (TransformPtr trf);
public:
  static MoveMoonPtr Make (TransformPtr trf);
  virtual void Update (float dt);
};