
#include "Grid.h"
#include "../Render/RenderEngine.h"

CGrid::CGrid(size_t _uRows, size_t _uColumns)
  : m_uNumberOfRows(_uRows),
  m_uNumberOfColumns(_uColumns),
  m_bActive(true)
{
  CRenderEngine::Get().InsertExternalDrawFunction(this, &CGrid::Draw);

  for (size_t uCell = 0; uCell < _uRows * _uColumns; uCell++)
  {
    m_cells.push_back(CRectangle());
  }
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

void CGrid::ActiveRectangle(size_t _uRow, size_t _uCol)
{
  size_t uIndex = GetIndexFromMatrixCoordenates(_uRow, _uCol);
  ensure(uIndex < m_uNumberOfRows* m_uNumberOfColumns);
  m_cells[uIndex].Active();
}

void CGrid::DeactiveRectangle(size_t _uRow, size_t _uCol)
{
  size_t uIndex = GetIndexFromMatrixCoordenates(_uRow, _uCol);
  ensure(uIndex < m_uNumberOfRows* m_uNumberOfColumns);
  m_cells[uIndex].Deactive();
}

void CGrid::SetRectangleColor(size_t _uRow, size_t _uCol, float _tColor[4])
{
  size_t uIndex = GetIndexFromMatrixCoordenates(_uRow, _uCol);
  ensure(uIndex < m_uNumberOfRows* m_uNumberOfColumns);
  m_cells[uIndex].SetColor(_tColor[0], _tColor[1], _tColor[2]);
}

void CGrid::Draw(void* _pInstance, const Vector2 & _screenSize)
{
  CGrid* pGridInstance = reinterpret_cast<CGrid*>(_pInstance);
  if (pGridInstance != nullptr && pGridInstance->m_bActive)
  {
    pGridInstance->Draw_Internal(_screenSize);
  }
}

void CGrid::Draw_Internal(const Vector2& _screenSize)
{
  DrawGrid(_screenSize);
  DrawShapes(_screenSize);
}

void CGrid::DrawGrid(const Vector2& _screenSize) const
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

void CGrid::DrawShapes(const Vector2& _screenSize)
{
  Vector2 size(
    _screenSize.GetX() / m_uNumberOfColumns,
    _screenSize.GetY() / m_uNumberOfRows
  );
  for (size_t uIndex = 0; uIndex < GetSize(); ++uIndex)
  {
    CRectangle& item = m_cells[uIndex];
    size_t uRow, uCol;
    GetMatrixCoordenatesFromIndex(uIndex, uRow, uCol);
    Vector2 position(
      uCol * _screenSize.GetX() / m_uNumberOfColumns,
      uRow * _screenSize.GetY() / m_uNumberOfRows
    );
    item.SetPosition(position);
    item.SetSize(size);
    item.Draw();
  }
}

size_t CGrid::GetIndexFromMatrixCoordenates(size_t _uRow, size_t _uCol) const
{
  return _uRow * m_uNumberOfColumns + _uCol;
}

void CGrid::GetMatrixCoordenatesFromIndex(size_t _uIndex, size_t& uRow_, size_t& uCol_) const
{
  uCol_ = static_cast<size_t>(static_cast<int>(_uIndex) % static_cast<int>(m_uNumberOfColumns));
  uRow_ = _uIndex / m_uNumberOfColumns;
}
