#pragma once

#include "Utils.h"

namespace Pathfinding
{
  class CNode
  {
  public:

    CNode(Vec2 _coordenates, CNode* _pParent = nullptr);

    float GetScore() const;
    Vec2 GetCoordenates() const;

  private:

    CNode* m_pParent;
    float m_h;
    float m_g;
    Vec2 m_coordenates;
  };
}

