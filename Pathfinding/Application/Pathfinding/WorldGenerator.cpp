#include "WorldGenerator.h"
#include "Heuristic.h"
#include "Utils.h"

Pathfinding::CWorldGenerator::CWorldGenerator(const Vec2& _worldSize)
  : m_grid(_worldSize.GetX(), _worldSize.GetY())
{
  m_openNodes.reserve(m_grid.GetSize());
  m_closedNodes.reserve(m_grid.GetSize());
  m_pHeuristicFunction = std::bind(&Heuristics::Manhattan, std::placeholders::_1, std::placeholders::_2);
  m_origin = Vec2(0, 0);
  m_destiny = Vec2(_worldSize.GetX() - 1, _worldSize.GetY() - 1);
}

void Pathfinding::CWorldGenerator::SetOrigin(const Vec2& _origin)
{
  m_origin = _origin;
}

void Pathfinding::CWorldGenerator::SetDestiny(const Vec2& _destiny)
{
  m_destiny = _destiny;
}

void Pathfinding::CWorldGenerator::SetHeuristic(HeuristicFunction _pFunction)
{
  m_pHeuristicFunction = std::bind(_pFunction, std::placeholders::_1, std::placeholders::_2);
}

void Pathfinding::CWorldGenerator::Update()
{
  std::vector<CNode*>::iterator pLessScoreNode = GetLessScoreNode();
  m_closedNodes.push_back(*pLessScoreNode);
  m_openNodes.erase(pLessScoreNode);
  if (CheckGoalAchieved(*pLessScoreNode))
  {
    // TODO terminar
  }
  int tDirections[4][2] = {
    {0, 1}, {1, 0}, {-1, 0}, {0, -1}
  };
  for (uint uIndex = 0; uIndex < 4; ++uIndex)
  {
    Vec2 newCoordenates(
      (*pLessScoreNode)->GetCoordenates().GetX() + tDirections[uIndex][0],
      (*pLessScoreNode)->GetCoordenates().GetY() + tDirections[uIndex][1]
    );
    float totalCost = (*pLessScoreNode)->GetScore() + 1.f;
    CNode* pNewNode = FindNode(newCoordenates);
    if (pNewNode == nullptr)
    {
      // TODO Crear nuevo nodo asociando costes
    }
    else
    {
      // TODO Corregir el nodo repetido con el menor coste
    }
  }
}

std::vector<Pathfinding::CNode*>::iterator Pathfinding::CWorldGenerator::GetLessScoreNode()
{
  std::vector<CNode*>::iterator lessScoreIterator = m_openNodes.begin();
  for (std::vector<CNode*>::iterator iterator = m_openNodes.begin() + 1; iterator != m_openNodes.end(); ++iterator)
  {
    if ((*iterator)->GetScore() < (*lessScoreIterator)->GetScore())
    {
      lessScoreIterator = iterator;
    }
  }
  return lessScoreIterator;
}

void Pathfinding::CWorldGenerator::UpdateGrid()
{
  uint uActiveNode = 0;
  for (uint uIndex = 0; uIndex < m_openNodes.size(); ++uIndex)
  {
    CNode* pNode = m_openNodes[uIndex];
    if (pNode->GetScore() < m_openNodes[uActiveNode]->GetScore())
    {
      uActiveNode = uIndex;
    }
    float tColor[] = { 0.f, 0.7f, 0.9f, 1.f };
    m_grid.ActiveRectangle(pNode->GetCoordenates().GetX(), pNode->GetCoordenates().GetY());
    m_grid.SetRectangleColor(pNode->GetCoordenates().GetX(), pNode->GetCoordenates().GetY(), tColor);
  }
  {
    float tColor[] = { 0.9f, 0.7f, 0.9f, 1.f };
    m_grid.SetRectangleColor(m_openNodes[uActiveNode]->GetCoordenates().GetX(), m_openNodes[uActiveNode]->GetCoordenates().GetY(), tColor);
  }
  for (uint uIndex = 0; uIndex < m_closedNodes.size(); ++uIndex)
  {
    CNode* pNode = m_closedNodes[uIndex];
    float tColor[] = { 0.9f, 0.3f, 0.f, 1.f };
    m_grid.SetRectangleColor(pNode->GetCoordenates().GetX(), pNode->GetCoordenates().GetY(), tColor);
  }
}

bool Pathfinding::CWorldGenerator::CheckGoalAchieved(CNode* _pCurrentNode) const
{
  return _pCurrentNode->GetCoordenates() == m_destiny;
}
