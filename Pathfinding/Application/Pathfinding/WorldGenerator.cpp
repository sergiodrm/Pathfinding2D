#include "WorldGenerator.h"
#include "Heuristic.h"
#include "Utils.h"

Pathfinding::CWorldGenerator::CWorldGenerator(const Vec2& _worldSize)
  : m_grid(_worldSize.GetX(), _worldSize.GetY())
{
  m_pHeuristicFunction = std::bind(&Heuristics::Euclidean, std::placeholders::_1, std::placeholders::_2);
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

void Pathfinding::CWorldGenerator::Init(const Vec2& _origin, const Vec2& _destiny)
{
  m_origin = _origin;
  m_destiny = _destiny;
  m_bPathFound = false;
  m_openNodes.clear();
  m_closedNodes.clear();
  m_openNodes.reserve(m_grid.GetSize());
  m_closedNodes.reserve(m_grid.GetSize());
  CNode* pInit = new CNode(m_origin, nullptr);
  pInit->SetCostG(0);
  pInit->SetCostH(m_pHeuristicFunction(m_origin, m_destiny));
  m_openNodes.push_back(pInit);
  m_grid.ActiveRectangle(_origin.GetY(), _origin.GetX());
  m_grid.ActiveRectangle(_destiny.GetY(), _destiny.GetX());
  {
    float tColor[4] = { 0.2f, 0.f, 0.7f, 1.f };
    m_grid.SetRectangleColor(_origin.GetY(), _origin.GetX(), tColor);
  }
  {
    float tColor[4] = { 0.2f, 0.7f, 0.f, 1.f };
    m_grid.SetRectangleColor(_destiny.GetY(), _destiny.GetX(), tColor);
  }
}

void Pathfinding::CWorldGenerator::PathfindingSlot()
{
  if (!m_bPathFound)
  {
    std::vector<CNode*>::iterator pLessScoreNode = GetLessScoreNode();
    m_closedNodes.push_back(*pLessScoreNode);
    CNode* pCurrentNode = *pLessScoreNode;
    m_openNodes.erase(pLessScoreNode);
    if (CheckGoalAchieved(pCurrentNode))
    {
      // TODO terminar
      MakePath(pCurrentNode);
      m_bPathFound = true;
    }
    else
    {
      int tDirections[4][2] = {
        {0, 1}, {1, 0}, {-1, 0}, {0, -1}
      };
      for (uint uIndex = 0; uIndex < 4; ++uIndex)
      {
        Vec2 newCoordenates(
          pCurrentNode->GetCoordenates().GetX() + tDirections[uIndex][0],
          pCurrentNode->GetCoordenates().GetY() + tDirections[uIndex][1]
        );

        if (CheckCollision(newCoordenates))
        {
          float totalCost = pCurrentNode->GetCostG() + 1.f;
          CNode* pNewNode = FindNode(m_openNodes, newCoordenates);
          if (pNewNode == nullptr)
          {
            pNewNode = FindNode(m_closedNodes, newCoordenates);
            if (pNewNode == nullptr)
            {
              pNewNode = new CNode(newCoordenates, pCurrentNode);
              pNewNode->SetCostG(totalCost);
              pNewNode->SetCostH(m_pHeuristicFunction(newCoordenates, m_destiny));
              m_openNodes.push_back(pNewNode);
            }
            else if(totalCost < pNewNode->GetCostG())
            {
              pNewNode->SetParent(pCurrentNode);
              pNewNode->SetCostG(totalCost);
              for (std::vector<CNode*>::iterator it = m_closedNodes.begin(); it != m_closedNodes.end(); ++it)
              {
                if (*it == pNewNode)
                {
                  m_closedNodes.erase(it);
                  break;
                }
              }
              m_openNodes.push_back(pNewNode);
            }
          }
          else if (totalCost < pNewNode->GetCostG())
          {
            pNewNode->SetParent(pCurrentNode);
            pNewNode->SetCostG(totalCost);
          }
        }
      }
      UpdateGrid(pCurrentNode->GetCoordenates());
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

void Pathfinding::CWorldGenerator::UpdateGrid(const Vec2& _currentPosition)
{
  for (uint uIndex = 0; uIndex < m_openNodes.size(); ++uIndex)
  {
    CNode* pNode = m_openNodes[uIndex];
    if (pNode->GetCoordenates() != m_origin && pNode->GetCoordenates() != m_destiny)
    {
      SColor color = GetColor(pNode->GetCoordenates(), true);
      m_grid.ActiveRectangle(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX());
      m_grid.SetRectangleColor(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX(), color.m_tColor);
    }
  }
  for (uint uIndex = 0; uIndex < m_closedNodes.size(); ++uIndex)
  {
    CNode* pNode = m_closedNodes[uIndex];
    if (pNode->GetCoordenates() != m_origin && pNode->GetCoordenates() != m_destiny)
    {
      SColor color = GetColor(pNode->GetCoordenates(), false);
      m_grid.ActiveRectangle(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX());
      m_grid.SetRectangleColor(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX(), color.m_tColor);
    }
  }
  if (_currentPosition != m_origin && _currentPosition != m_destiny)
  {
    float tColor[] = { 1.f, 1.f, 1.f, 1.f };
    m_grid.SetRectangleColor(_currentPosition.GetY(), _currentPosition.GetX(), tColor);
  }
}

bool Pathfinding::CWorldGenerator::CheckGoalAchieved(CNode* _pCurrentNode) const
{
  return _pCurrentNode->GetCoordenates() == m_destiny;
}

bool Pathfinding::CWorldGenerator::CheckCollision(const Vec2& _coordenates) const
{
  return _coordenates.GetX() >= 0 && _coordenates.GetX() < m_grid.GetNumOfColumns() &&
    _coordenates.GetY() >= 0 && _coordenates.GetY() < m_grid.GetNumOfRows();
}

Pathfinding::CNode* Pathfinding::CWorldGenerator::FindNode(std::vector<CNode*>& _container, const Vec2& _coordenates) const
{
  for (CNode* pIterator : _container)
  {
    if (pIterator->GetCoordenates() == _coordenates)
      return pIterator;
  }
  return nullptr;
}

void Pathfinding::CWorldGenerator::MakePath(CNode* _pGoal)
{
  CNode* pCurrent = _pGoal;
  while (pCurrent != nullptr)
  {
    SColor color = GetColor(pCurrent->GetCoordenates());
    m_grid.SetRectangleColor(pCurrent->GetCoordenates().GetX(), pCurrent->GetCoordenates().GetY(), color.m_tColor);
    pCurrent = pCurrent->GetParent();
  }
}

Pathfinding::SColor Pathfinding::CWorldGenerator::GetColor(const Vec2& _coordenates, bool _bInOpenList)
{
  if (_coordenates == m_origin)
  {
    SColor color({ 0.f, 1.f, 0.f, 1.f });
    return color;
  }
  if(_coordenates == m_destiny)
  {
    SColor color({ 1.f, 0.f, 0.f, 1.f });
    return color;
  }
  if (_bInOpenList)
  {
    SColor color({ 1.f, 1.f, 0.f, 1.f });
    return color;
  }
  SColor color({ 1.f, 0.f, 1.f, 1.f });
  return color;
}