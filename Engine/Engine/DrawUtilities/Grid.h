#pragma once

#include "Engine/MacroObject.h"
#include "Engine/Math/Vector2.h"
#include "Shapes.h"
#include <vector>

class ENGINE_API CGrid
{
private:

  size_t m_uNumberOfColumns;
  size_t m_uNumberOfRows;
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

  inline size_t GetSize() const { return m_uNumberOfRows * m_uNumberOfColumns; }
  inline size_t GetNumOfRows() const { return m_uNumberOfRows; }
  inline size_t GetNumOfColumns() const { return m_uNumberOfColumns; }

  static void Draw(void* _pInstance, const Vector2& _screenSize);

private:

  void Draw_Internal(const Vector2& _screenSize);
  void DrawGrid(const Vector2& _screenSize) const;
  void DrawShapes(const Vector2& _screenSize);
  size_t GetIndexFromMatrixCoordenates(size_t _uRow, size_t _uCol) const;
  void GetMatrixCoordenatesFromIndex(size_t _uIndex, size_t& uRow_, size_t& uCol_) const;

};

