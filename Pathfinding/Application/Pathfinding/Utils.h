#pragma once

#include <functional>


namespace Pathfinding
{
  class Vec2;
  typedef unsigned int uint;
  typedef std::function<float(Vec2, Vec2)> HeuristicFunction;
  
  
  class Vec2
  {
  public:

    Vec2(uint _x = 0, uint _y = 0);

    uint GetX() const;
    uint GetY() const;
    void SetX(uint _x);
    void SetY(uint _y);

    bool operator==(const Vec2& _other) const;
    bool operator!=(const Vec2& _other) const;
    Vec2 operator-(const Vec2& _other) const;

  private:
    uint m_x;
    uint m_y;
  };
}
