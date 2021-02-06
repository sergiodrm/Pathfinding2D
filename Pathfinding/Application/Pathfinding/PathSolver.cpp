#include "PathSolver.h"

#include <algorithm>
#include <string>

#include "Engine/Timer/TimeManager.h"
#include "Engine/MacroObject.h"
#include "Heuristic.h"

#define RENDER_FEEDBACK 0

Pathfinding::CPathSolver::CPathSolver()
  : m_pHeuristicFunction(std::bind(&Heuristics::Euclidean, std::placeholders::_1, std::placeholders::_2)),
  m_origin(0, 0), m_destiny(0, 0), m_pCollisionMap(nullptr)
{}

void Pathfinding::CPathSolver::SetOrigin(const Vec2& _origin)
{
  m_origin = _origin;
}

void Pathfinding::CPathSolver::SetDestiny(const Vec2& _destiny)
{
  m_destiny = _destiny;
}

void Pathfinding::CPathSolver::SetHeuristic(HeuristicFunction _pFunction)
{
  m_pHeuristicFunction = std::bind(_pFunction, std::placeholders::_1, std::placeholders::_2);
}

void Pathfinding::CPathSolver::Init(CMap* _collisionMap, const Vec2& _origin, const Vec2& _destiny)
{
  m_pCollisionMap = _collisionMap;
  m_origin = _origin;
  m_destiny = _destiny;
  m_bPathFound = false;
  m_openNodes.clear();
  m_closedNodes.clear();
  m_openNodes.reserve(m_pCollisionMap->GetSize());
  m_closedNodes.reserve(m_pCollisionMap->GetSize());
  CNode* pInit = new CNode(m_origin, nullptr);
  pInit->SetCostG(0);
  pInit->SetCostH(m_pHeuristicFunction(m_origin, m_destiny));
  m_openNodes.push_back(pInit);
#if RENDER_FEEDBACK
  m_pCollisionMap->ActiveRectangle(_origin.GetY(), _origin.GetX());
  m_pCollisionMap->ActiveRectangle(_destiny.GetY(), _destiny.GetX());
  {
    float tColor[4] = { 0.2f, 0.f, 0.7f, 1.f };
    m_pCollisionMap->SetRectangleColor(_origin.GetY(), _origin.GetX(), tColor);
  }
  {
    float tColor[4] = { 0.2f, 0.7f, 0.f, 1.f };
    m_pCollisionMap->SetRectangleColor(_destiny.GetY(), _destiny.GetX(), tColor);
  }
#endif
}

void Pathfinding::CPathSolver::PathfindingSlot()
{
#if RENDER_FEEDBACK
  if (!m_bPathFound)
  {
#else
  CTimeManager::GetInstance().StartTimer();
  while (!m_bPathFound)
  {
#endif // 0
    SortVector(m_openNodes);
    CNode* pCurrentNode = GetNextPathNode();
    UpdateLists();
    
    if (CheckGoalAchieved(pCurrentNode))
    {
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
          CreateNode(pCurrentNode, newCoordenates);
        }
      }
#if RENDER_FEEDBACK
      UpdateGrid(pCurrentNode->GetCoordenates());
#endif // RENDER_FEEDBACK
    }
  }
#if !RENDER_FEEDBACK
  static bool bPrint = true;
  if (bPrint)
  {
    PRINT_LOG("Pathfinding time: %.5f seconds", CTimeManager::GetInstance().StopTimer());
    bPrint = false;
  }
#endif
}

void Pathfinding::CPathSolver::Shutdown()
{
  CMap::DestroyMap(m_pCollisionMap);
}

Pathfinding::CNode* Pathfinding::CPathSolver::GetNextPathNode()
{
  return m_openNodes.front();
}

void Pathfinding::CPathSolver::UpdateLists()
{
  CNode* pCurrentNode = GetNextPathNode();
  m_closedNodes.push_back(pCurrentNode);
  m_openNodes.erase(m_openNodes.begin());
}

void Pathfinding::CPathSolver::UpdateGrid(const Vec2& _currentPosition)
{
  for (uint uIndex = 0; uIndex < m_openNodes.size(); ++uIndex)
  {
    CNode* pNode = m_openNodes[uIndex];
    if (pNode->GetCoordenates() != m_origin && pNode->GetCoordenates() != m_destiny)
    {
      SColor color = GetColor(pNode->GetCoordenates(), true);
      m_pCollisionMap->ActiveRectangle(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX());
      m_pCollisionMap->SetRectangleColor(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX(), color.m_tColor);
    }
  }
  for (uint uIndex = 0; uIndex < m_closedNodes.size(); ++uIndex)
  {
    CNode* pNode = m_closedNodes[uIndex];
    if (pNode->GetCoordenates() != m_origin && pNode->GetCoordenates() != m_destiny)
    {
      SColor color = GetColor(pNode->GetCoordenates(), false);
      m_pCollisionMap->ActiveRectangle(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX());
      m_pCollisionMap->SetRectangleColor(pNode->GetCoordenates().GetY(), pNode->GetCoordenates().GetX(), color.m_tColor);
    }
  }
  if (_currentPosition != m_origin && _currentPosition != m_destiny)
  {
    float tColor[] = { 1.f, 1.f, 1.f, 1.f };
    m_pCollisionMap->SetRectangleColor(_currentPosition.GetY(), _currentPosition.GetX(), tColor);
  }
}

bool Pathfinding::CPathSolver::CheckGoalAchieved(CNode* _pCurrentNode) const
{
  return _pCurrentNode->GetCoordenates() == m_destiny;
}

bool Pathfinding::CPathSolver::CheckCollision(const Vec2& _coordenates) const
{
  return _coordenates.GetX() >= 0 && _coordenates.GetX() < m_pCollisionMap->GetNumOfColumns() &&
    _coordenates.GetY() >= 0 && _coordenates.GetY() < m_pCollisionMap->GetNumOfRows() &&
    !m_pCollisionMap->GetCellState(_coordenates.GetY(), _coordenates.GetX());
}

void Pathfinding::CPathSolver::MakePath(CNode* _pGoal)
{
  CNode* pCurrent = _pGoal;
  while (pCurrent != nullptr)
  {
    SColor color({NORMALIZE_RGB(29), NORMALIZE_RGB(131), NORMALIZE_RGB(72), 1.f});
    if (pCurrent->GetCoordenates() == m_destiny || pCurrent->GetCoordenates() == m_origin)
    {
      color = GetColor(pCurrent->GetCoordenates());
    }
#if !RENDER_FEEDBACK
    m_pCollisionMap->ActiveRectangle(pCurrent->GetCoordenates().GetY(), pCurrent->GetCoordenates().GetX());
#endif
    m_pCollisionMap->SetRectangleColor(pCurrent->GetCoordenates().GetY(), pCurrent->GetCoordenates().GetX(), color.m_tColor);
    pCurrent = pCurrent->GetParent();
  }
}

Pathfinding::SColor Pathfinding::CPathSolver::GetColor(const Vec2& _coordenates, bool _bInOpenList) const
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
    SColor color({ NORMALIZE_RGB(212), NORMALIZE_RGB(172), NORMALIZE_RGB(13), 1.f });
    return color;
  }
  SColor color({ NORMALIZE_RGB(133), NORMALIZE_RGB(193), NORMALIZE_RGB(206), 1.f });
  return color;
}

void Pathfinding::CPathSolver::CreateNode(CNode* _pParent, const Vec2& _coordenates)
{
  CNode* pNodeInOpenList = FindNode(m_openNodes, _coordenates);
  CNode* pNodeInClosedList = FindNode(m_closedNodes, _coordenates);
  int deltaX = static_cast<int>(_coordenates.GetX()) - static_cast<int>(_pParent->GetCoordenates().GetX());
  int deltaY = static_cast<int>(_coordenates.GetY()) - static_cast<int>(_pParent->GetCoordenates().GetY());
  float costAdded = static_cast<float>(deltaX + deltaY);
  float totalCost = _pParent->GetCostG() + costAdded;
  if (pNodeInOpenList == nullptr && pNodeInClosedList == nullptr)
  {
    CNode* pNewNode = new CNode(_coordenates, _pParent);
    pNewNode->SetCostG(totalCost);
    pNewNode->SetCostH(m_pHeuristicFunction(_coordenates, m_destiny));
    m_openNodes.push_back(pNewNode);
  }
  else
  {
    CNode* pExistingNode = pNodeInClosedList != nullptr ? pNodeInClosedList : pNodeInOpenList;
    if (totalCost < pExistingNode->GetCostG())
    {
      pExistingNode->SetCostG(totalCost);
      pExistingNode->SetParent(_pParent);
      if (pNodeInClosedList != nullptr)
      {
        std::vector<CNode*>::iterator itToDelete;
        for (itToDelete = m_closedNodes.begin(); itToDelete != m_closedNodes.end(); ++itToDelete)
        {
          if (*itToDelete == pNodeInClosedList)
          {
            m_closedNodes.erase(itToDelete);
            break;
          }
        }
        m_openNodes.push_back(pExistingNode);
      }
    }
  }
}

Pathfinding::CNode* Pathfinding::CPathSolver::FindNode(std::vector<CNode*>& _container, const Vec2& _coordenates)
{
  for (CNode* pIterator : _container)
  {
    if (pIterator->GetCoordenates() == _coordenates)
      return pIterator;
  }
  return nullptr;
}

void Pathfinding::CPathSolver::SortVector(std::vector<CNode*>& _vector_)
{
  std::sort(_vector_.begin(), _vector_.end(), [](const CNode* _a, const CNode* _b) {return _a->GetScore() < _b->GetScore(); });
}
