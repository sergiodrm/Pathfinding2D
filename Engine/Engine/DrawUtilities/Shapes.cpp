#include "Shapes.h"
#include "Engine/Render/RenderEngine.h"

CShape::CShape()
  : m_position(Vector2(0.f, 0.f)),
  m_size(Vector2(0.f, 0.f)),
  m_tColor{ 1.f, 1.f, 1.f, 1.f }
{}

CShape::CShape(const Vector2& _position, const Vector2& _size)
  : m_position(_position),
  m_size(_size),
  m_tColor{ 1.f, 1.f, 1.f, 1.f }
{}

void CShape::Active()
{
  m_bActive = true;
}

void CShape::Deactive()
{
  m_bActive = false;
}

void CShape::GetColor(float& fR_, float& fG_, float& fB_) const
{
  fR_ = m_tColor[0];
  fG_ = m_tColor[1];
  fB_ = m_tColor[2];
}

void CShape::SetColor(float _fR, float _fG, float _fB)
{
  m_tColor[0] = _fR;
  m_tColor[1] = _fG;
  m_tColor[2] = _fB;
}

void CRectangle::Draw() const
{
  if (m_bActive)
  {
    CRenderEngine::SetColor(m_tColor[0], m_tColor[1], m_tColor[2]);
    CRenderEngine::DrawRectangle(m_position, m_size);
  }
}
