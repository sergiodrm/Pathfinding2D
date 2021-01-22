
#include "Grid.h"
#include "../Render/RenderEngine.h"

CGrid::CGrid(size_t _uRows, size_t _uColumns)
  : m_uNumberOfRows(_uRows),
  m_uNumberOfColumns(_uColumns),
  m_bActive(true)
{
  CRenderEngine::Get().InsertExternalDrawFunction(this, &CGrid::Draw);
}

void CGrid::Activate()
{
  m_bActive = true;
}

void CGrid::Deactivate()
{
  m_bActive = false;
}

bool CGrid::IsActive() const
{
  return m_bActive;
}

void CGrid::Draw(void* _pInstance, const Vector2 & _screenSize)
{
  CGrid* pGridInstance = reinterpret_cast<CGrid*>(_pInstance);
  if (pGridInstance != nullptr && pGridInstance->m_bActive)
  {
    pGridInstance->Draw_Internal(_screenSize);
  }
}

void CGrid::Draw_Internal(const Vector2& _screenSize) const
{
  CRenderEngine::SetColor(0.9f);
  for (size_t uRow = 1; uRow < m_uNumberOfRows; uRow++)
  {
    Vector2 origin(
      0.f,
      static_cast<float>(uRow) * _screenSize.GetY() / static_cast<float>(m_uNumberOfRows)
    );
    Vector2 destiny(
      _screenSize.GetX(),
      static_cast<float>(uRow) * _screenSize.GetY() / static_cast<float>(m_uNumberOfRows)
    );
    CRenderEngine::DrawLine(origin, destiny);
  }
  for (size_t uCol = 1; uCol < m_uNumberOfColumns; uCol++)
  {
    Vector2 origin(
      static_cast<float>(uCol) * _screenSize.GetX() / static_cast<float>(m_uNumberOfColumns),
      0.f
    );
    Vector2 destiny(
      static_cast<float>(uCol) * _screenSize.GetX() / static_cast<float>(m_uNumberOfColumns),
      _screenSize.GetY()
    );
    CRenderEngine::DrawLine(origin, destiny);
  }
}
