#pragma once

#include "../MacroObject.h"
#include "../Math/Vector2.h"

class ENGINE_API CGrid
{
private:

  size_t m_uNumberOfColumns;
  size_t m_uNumberOfRows;
  bool m_bActive;

public:

  CGrid(size_t _uRows, size_t _uColumns);

  void Activate();
  void Deactivate();
  bool IsActive() const;

  static void Draw(void* _pInstance, const Vector2& _screenSize);

private:

  void Draw_Internal(const Vector2& _screenSize) const;

};

