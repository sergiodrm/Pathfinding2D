#include "Utils.h"

Pathfinding::Vec2::Vec2(uint _x, uint _y)
  : m_x(_x), m_y(_y)
{}

Pathfinding::uint Pathfinding::Vec2::GetX() const
{
  return m_x;
}

Pathfinding::uint Pathfinding::Vec2::GetY() const
{
  return m_y;
}

void Pathfinding::Vec2::SetX(uint _x)
{
  m_x = _x;
}

void Pathfinding::Vec2::SetY(uint _y)
{
  m_y = _y;
}

bool Pathfinding::Vec2::operator==(const Vec2& _other)
{
  return m_x == _other.m_x && m_y == _other.m_y;
}
