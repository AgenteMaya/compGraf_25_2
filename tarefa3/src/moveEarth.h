#include <memory>

class MoveEarth;
using MoveEarthPtr = std::shared_ptr<MoveEarth>;

#include "engine.h"
#include "transform.h"

class MoveEarth : public Engine 
{
  TransformPtr m_trf;
protected:
  MoveEarth (TransformPtr trf);
public:
  static MoveEarthPtr Make (TransformPtr trf);
  virtual void Update (float dt);
};