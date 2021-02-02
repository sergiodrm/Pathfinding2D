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

float Pathfinding::CNode::GetCostG() const
{
  return m_g;
}
float Pathfinding::CNode::GetCostH() const
{
  return m_h;
}

Pathfinding::CNode* Pathfinding::CNode::GetParent() const
{
  return m_pParent;
}

void Pathfinding::CNode::SetCostG(float _g)
{
  m_g = _g;
}
void Pathfinding::CNode::SetCostH(float _h)
{
  m_h = _h;
}

void Pathfinding::CNode::SetParent(CNode* _pParentNode)
{
  m_pParent = _pParentNode;
}

