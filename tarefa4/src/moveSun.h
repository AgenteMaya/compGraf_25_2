#include <memory>

class MoveSun;
using MoveSunPtr = std::shared_ptr<MoveSun>;

#include "engine.h"
#include "transform.h"

class MoveSun : public Engine 
{
  TransformPtr m_trf;
protected:
  MoveSun (TransformPtr trf);
public:
  static MoveSunPtr Make (TransformPtr trf);
  virtual void Update (float dt);
};