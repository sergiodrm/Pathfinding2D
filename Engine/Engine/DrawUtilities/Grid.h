#pragma once

#include "Engine/MacroObject.h"
#include "Engine/Math/Vector2.h"
#include "Shapes.h"
#include <vector>

class ENGINE_API CGrid
{
  DECLARE_BASE_CLASS(CGrid)

protected:

  size_t m_numberOfColumns;
  size_t m_numberOfRows;
  bool m_bActive;
  std::vector<CRectangle> m_cells;

public:

  CGrid(size_t _uRows, size_t _uColumns);

  void Activate();
  void Deactivate();
  bool IsActive() const;

  void ActiveRectangle(size_t _uRow, size_t _uCol);
  void DeactiveRectangle(size_t _uRow, size_t _uCol);
  void SetRectangleColor(size_t _uRow, size_t _uCol, float _tColor[4]);

  inline size_t GetSize() const { return m_numberOfRows * m_numberOfColumns; }
  inline size_t GetNumOfRows() const { return m_numberOfRows; }
  inline size_t GetNumOfColumns() const { return m_numberOfColumns; }

  static void Draw(void* _pInstance, const Vector2& _screenSize);

protected:

  virtual void Draw_Internal(const Vector2& _screenSize);
  void DrawGrid(const Vector2& _screenSize) const;
  void DrawShapes(const Vector2& _screenSize);

protected:

  size_t RC2Index(size_t _uRow, size_t _uCol) const;
  void Index2RC(size_t _uIndex, size_t& uRow_, size_t& uCol_) const;

};

