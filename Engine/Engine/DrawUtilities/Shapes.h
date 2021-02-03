#pragma once

#include "Engine/Math/Vector2.h"
#include "Engine/MacroObject.h"

class ENGINE_API CShape
{
protected:

  Vector2 m_position;
  Vector2 m_size;
  bool m_bActive;
  float m_tColor[4];

public:

  CShape();
  CShape(const Vector2& _position, const Vector2& _size);

  void Active();
  void Deactive();
  inline bool IsActive() const { return m_bActive; }

  inline const Vector2& GetPosition() const { return m_position; }
  inline const Vector2& GetSize() const { return m_size; }
  inline void SetPosition(const Vector2& _position) { m_position = _position; }
  inline void SetSize(const Vector2& _size) { m_size = _size; }
  void GetColor(float& fR_, float& fG_, float& fB_) const;
  void SetColor(float _fR, float _fG, float _fB);

  virtual void Draw() const = 0;

};


class ENGINE_API CRectangle : public CShape
{
public:
  virtual void Draw() const override;
};
