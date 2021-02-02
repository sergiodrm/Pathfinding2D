#include "Node.h"


Pathfinding::CNode::CNode(Vec2 _coordenates, CNode* _pParent)
  : m_coordenates(_coordenates), m_pParent(_pParent),
  m_g(0.f), m_h(0.f)
{}

float Pathfinding::CNode::GetScore() const
{
  return m_g + m_h;
}

Pathfinding::Vec2 Pathfinding::CNode::GetCoordenates() const
{
  return m_coordenates;
}

