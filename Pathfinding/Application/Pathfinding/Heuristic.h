#pragma once

#include "Utils.h"

namespace Pathfinding
{
  namespace Heuristics
  {
    float Euclidean(const Vec2& _origin, const Vec2& _destiny);
    float Manhattan(const Vec2& _origin, const Vec2& _destiny);
  }
}

