#pragma once

#include "Utils.h"

namespace Pathfinding
{
  class CNode
  {
  public:

    CNode(const Vec2& _coordenates, CNode* _pParent = nullptr);

    float GetScore() const;
    Vec2 GetCoordenates() const;

    float GetCostG() const;
    float GetCostH() const;
    CNode* GetParent() const;
    void SetCostG(float _g);
    void SetCostH(float _h);
    void SetParent(CNode* _pParentNode);

  private:

    CNode* m_pParent;
    float m_h;
    float m_g;
    Vec2 m_coordenates;
  };
}

