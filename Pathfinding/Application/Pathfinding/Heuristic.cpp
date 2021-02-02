#include "Heuristic.h"
#include <math.h>
float Pathfinding::Heuristics::Euclidean(const Vec2& _origin, const Vec2& _destiny)
{
  Vec2 delta = _destiny - _origin;
  return sqrtf(delta.GetX()*delta.GetX() + delta.GetY()*delta.GetY());
}
float Pathfinding::Heuristics::Manhattan(const Vec2& _origin, const Vec2& _destiny)
{
  Vec2 delta = _destiny - _origin;
  return delta.GetX() + delta.GetY();
}
