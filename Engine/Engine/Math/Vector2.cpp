#include "Vector2.h"

#include <math.h>

// ************************************************************************
// MATH
// ************************************************************************

bool Math::IsNearlyEqual(float _fValue1, float _fValue2, float _fTolerance)
{
  return _fValue1 <= _fValue2 + _fTolerance &&
    _fValue1 >= _fValue2 - _fTolerance;
}


// ************************************************************************
// Vector2
// ************************************************************************

// Constructores --------------------------------------

Vector2::Vector2() 
  : m_fX(0.f), m_fY(0.f)
{}

Vector2::Vector2(float _fX, float _fY)
  : m_fX(_fX), m_fY(_fY)
{}

// Operadores --------------------------------------

Vector2 Vector2::operator+(const Vector2& _rOther)
{
  return Vector2(m_fX + _rOther.m_fX, m_fY + _rOther.m_fY);
}

Vector2 Vector2::operator+(float _fValue)
{
  return Vector2(m_fX + _fValue, m_fY + _fValue);
}

Vector2& Vector2::operator+=(const Vector2& _rOther)
{
  m_fX += _rOther.m_fX;
  m_fY += _rOther.m_fY;
  return *this;
}

Vector2& Vector2::operator+=(float _fValue)
{
  m_fX += _fValue;
  m_fY += _fValue;
  return *this;
}

Vector2 Vector2::operator-(const Vector2& _rOther)
{
  return Vector2(m_fX - _rOther.m_fX, m_fY - _rOther.m_fY);
}

Vector2 Vector2::operator-(float _fValue)
{
  return Vector2(m_fX - _fValue, m_fY - _fValue);
}

Vector2& Vector2::operator-=(const Vector2& _rOther)
{
  m_fX += _rOther.m_fX;
  m_fY += _rOther.m_fY;
  return *this;
}

Vector2& Vector2::operator-=(float _fValue)
{
  m_fX -= _fValue;
  m_fY -= _fValue;
  return *this;
}

Vector2 Vector2::operator*(const Vector2& _rOther)
{
  return Vector2(m_fX * _rOther.m_fX, m_fY * _rOther.m_fY);
}

Vector2 Vector2::operator*(float _fValue)
{
  return Vector2(m_fX * _fValue, m_fY * _fValue);
}

Vector2& Vector2::operator*=(const Vector2& _rOther)
{
  m_fX *= _rOther.m_fX;
  m_fY *= _rOther.m_fY;
  return *this;
}

Vector2& Vector2::operator*=(float _fValue)
{
  m_fX *= _fValue;
  m_fY *= _fValue;
  return *this;
}

Vector2 Vector2::operator/(const Vector2& _rOther)
{
  return Vector2(m_fX / _rOther.m_fX, m_fY / _rOther.m_fY);
}

Vector2 Vector2::operator/(float _fValue)
{
  return Vector2(m_fX / _fValue, m_fY / _fValue);
}

Vector2& Vector2::operator/=(const Vector2& _rOther)
{
  m_fX /= _rOther.m_fX;
  m_fY /= _rOther.m_fY;
  return *this;
}

Vector2& Vector2::operator/=(float _fValue)
{
  m_fX /= _fValue;
  m_fY /= _fValue;
  return *this;
}

// Metodos -----------------------------------------------------

Vector2 Vector2::GetAbs() const
{
  return Vector2(fabsf(m_fX), fabsf(m_fY));
}

Vector2 Vector2::GetNormal() const
{
  return Vector2(-m_fY, m_fX);
}

float Vector2::Dot(const Vector2& _rOther) const
{
  return m_fX * _rOther.m_fX + m_fY * _rOther.m_fY;
}

float Vector2::Dot(const Vector2& _rV1, const Vector2& _rV2)
{
  return _rV1.Dot(_rV2);
}

float Vector2::Angle(const Vector2& _rOther) const
{
  //return Math::Deg2Rad(acosf(Dot(_rOther) / (Length() * _rOther.Length())));
  //return Math::Rad2Deg(atan2f(_rOther.m_fY - m_fY, _rOther.m_fX - m_fX));
  return Math::Rad2Deg(atan2f(_rOther.m_fY, _rOther.m_fX) - atan2f(m_fY, m_fX));
}

float Vector2::Angle(const Vector2& _rV1, const Vector2& _rV2)
{
  return _rV1.Angle(_rV2);
}

float Vector2::Distance(const Vector2& _rOther) const
{
  Vector2 vSubs(m_fX - _rOther.m_fX, m_fY - _rOther.m_fY);
  return vSubs.Length();
}

float Vector2::Distance(const Vector2& _rV1, const Vector2& _rV2)
{
  return _rV1.Distance(_rV2);
}

float Vector2::Length() const
{
  return sqrtf(powf(m_fX, 2.f) + powf(m_fY, 2.f));
}

float Vector2::Length(const Vector2& _rVector)
{
  return _rVector.Length();
}

bool Vector2::IsNormalized() const
{
  return Math::IsNearlyEqual(Length(), 1.f);
}

void Vector2::Normalize()
{
  float fLength = Length();
  m_fX /= fLength;
  m_fY /= fLength;
}

Vector2 operator+(const Vector2& _rVector, float _fScalar) { return Vector2(_rVector.GetX() + _fScalar, _rVector.GetY() + _fScalar); }

Vector2 operator-(const Vector2& _rVector, float _fScalar) { return Vector2(_rVector.GetX() - _fScalar, _rVector.GetY() - _fScalar); }

Vector2 operator*(const Vector2& _rVector, float _fScalar) { return Vector2(_rVector.GetX() * _fScalar, _rVector.GetY() * _fScalar); }

Vector2 operator/(const Vector2& _rVector, float _fScalar) { return Vector2(_rVector.GetX() / _fScalar, _rVector.GetY() / _fScalar); }
