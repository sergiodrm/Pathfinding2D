
#include "Grid.h"
#include "Engine/Render/RenderEngine.h"

CGrid::CGrid(size_t _uRows, size_t _uColumns)
  : m_numberOfRows(_uRows),
  m_numberOfColumns(_uColumns),
  m_bActive(true)
{
  CRenderEngine::Get().BindExternalDrawDelegate<CGrid, &CGrid::Draw>(this);

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
  size_t uIndex = RC2Index(_uRow, _uCol);
  ensure(uIndex < m_numberOfRows* m_numberOfColumns);
  m_cells[uIndex].Active();
}

void CGrid::DeactiveRectangle(size_t _uRow, size_t _uCol)
{
  size_t uIndex = RC2Index(_uRow, _uCol);
  ensure(uIndex < m_numberOfRows* m_numberOfColumns);
  m_cells[uIndex].Deactive();
}

void CGrid::SetRectangleColor(size_t _uRow, size_t _uCol, float _tColor[4])
{
  size_t uIndex = RC2Index(_uRow, _uCol);
  ensure(uIndex < m_numberOfRows* m_numberOfColumns);
  m_cells[uIndex].SetColor(_tColor[0], _tColor[1], _tColor[2]);
}

void CGrid::Draw(const Vector2& _screenSize)
{
  Draw_Internal(_screenSize); 
}

void CGrid::Draw_Internal(const Vector2& _screenSize)
{
  DrawShapes(_screenSize);
  DrawGrid(_screenSize);
}

void CGrid::DrawGrid(const Vector2& _screenSize) const
{
  CRenderEngine::SetColor(0.5f);
  for (size_t uRow = 1; uRow < m_numberOfRows; uRow++)
  {
    Vector2 origin(
      0.f,
      static_cast<float>(uRow) * _screenSize.GetY() / static_cast<float>(m_numberOfRows)
    );
    Vector2 destiny(
      _screenSize.GetX(),
      static_cast<float>(uRow) * _screenSize.GetY() / static_cast<float>(m_numberOfRows)
    );
    CRenderEngine::DrawLine(origin, destiny);
  }
  for (size_t uCol = 1; uCol < m_numberOfColumns; uCol++)
  {
    Vector2 origin(
      static_cast<float>(uCol) * _screenSize.GetX() / static_cast<float>(m_numberOfColumns),
      0.f
    );
    Vector2 destiny(
      static_cast<float>(uCol) * _screenSize.GetX() / static_cast<float>(m_numberOfColumns),
      _screenSize.GetY()
    );
    CRenderEngine::DrawLine(origin, destiny);
  }
}

void CGrid::DrawShapes(const Vector2& _screenSize)
{
  Vector2 size(
    _screenSize.GetX() / m_numberOfColumns,
    _screenSize.GetY() / m_numberOfRows
  );
  for (size_t uIndex = 0; uIndex < GetSize(); ++uIndex)
  {
    CRectangle& item = m_cells[uIndex];
    size_t uRow, uCol;
    Index2RC(uIndex, uRow, uCol);
    Vector2 position(
      uCol * _screenSize.GetX() / m_numberOfColumns,
      uRow * _screenSize.GetY() / m_numberOfRows
    );
    item.SetPosition(position);
    item.SetSize(size);
    item.Draw();
  }
}

size_t CGrid::RC2Index(size_t _uRow, size_t _uCol) const
{
  return _uRow * m_numberOfColumns + _uCol;
}

void CGrid::Index2RC(size_t _uIndex, size_t& uRow_, size_t& uCol_) const
{
  uCol_ = static_cast<size_t>(static_cast<int>(_uIndex) % static_cast<int>(m_numberOfColumns));
  uRow_ = _uIndex / m_numberOfColumns;
}
