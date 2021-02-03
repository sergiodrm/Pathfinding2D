#pragma once

#define M_PI 3.14159265358979323846f

#include "Engine/MacroObject.h"

namespace Math
{
  ENGINE_API bool IsNearlyEqual(float _fValue1, float _fValue2, float _fTolerance = 1.0e-4);

  template <typename T>
  ENGINE_API inline T Max(T _value1, T _value2) { return _value1 > _value2 ? _value1 : _value2; }

  template <typename T>
  ENGINE_API inline T Min(T _value1, T _value2) { return _value1 < _value2 ? _value1 : _value2; }

  template <typename T>
  ENGINE_API inline T Clamp(T _value, T _min, T _max)
  {
    return (_value >= _min && _value <= _max) ? _value : (_value < _min) ? _min : _max;
  }

  template <typename T>
  ENGINE_API inline T Abs(T _value) { return _value > 0 ? _value : -_value; }

  template <typename T>
  ENGINE_API inline bool InRange(T _value, T _min, T _max, bool _minIncluded = true, bool _maxIncluded = true)
  {
    if (_minIncluded && _maxIncluded)
    {
      return _value >= _min && _value <= _max;
    }
    else if (_minIncluded)
    {
      return _value >= _min && _value < _max;
    }
    else if (_maxIncluded)
    {
      return _value > _min && _value <= _max;
    }
    else return _value > _min && _value < _max;
  }

  ENGINE_API inline float Sign(float _fValue) { return _fValue >= 0 ? 1.f : -1.f; }

  ENGINE_API inline float Rad2Deg(float _fRad)
  {
    return _fRad * 180.f / M_PI;
  }

  ENGINE_API inline float Deg2Rad(float _fDeg)
  {
    return _fDeg * M_PI / 180.f;
  }
}

class ENGINE_API Vector2
{
public:

  // Constructores y destructor ------------------

  Vector2();
  Vector2(float _fX, float _fY);

  // TODO: constructor copia y con move semantics si el de por defecto no sirve
  //Vector2(const Vector2& _rOther);
  //Vector2(Vector2&& _rOther);
  //~Vector2();

  // Operadores ----------------------------------

  // TODO: si hace falta que no sea el de por defecto...
  //const Vector2& operator=(const Vector2& _rOther);
  //const Vector2& operator=(Vector2&& _rOther);

  Vector2 operator+(const Vector2& _rOther);
  Vector2 operator+(float _fValue);
  Vector2& operator+=(const Vector2& _rOther);
  Vector2& operator+=(float _fValue);
  Vector2 operator-(const Vector2& _rOther);
  Vector2 operator-(float _fValue);
  Vector2& operator-=(const Vector2& _rOther);
  Vector2& operator-=(float _fValue);
  Vector2 operator*(const Vector2& _rOther);
  Vector2 operator*(float _fValue);
  Vector2& operator*=(const Vector2& _rOther);
  Vector2& operator*=(float _fValue);
  Vector2 operator/(const Vector2& _rOther);
  Vector2 operator/(float _fValue);
  Vector2& operator/=(const Vector2& _rOther);
  Vector2& operator/=(float _fValue);

  // Metodos -------------------------------------

  inline float GetX() const { return m_fX; }
  inline float GetY() const { return m_fY; }
  inline void SetX(float _fX) { m_fX = _fX; }
  inline void SetY(float _fY) { m_fY = _fY; }

  Vector2 GetAbs() const;
  Vector2 GetNormal() const;

  float Dot(const Vector2& _rOther) const;
  static float Dot(const Vector2& _rV1, const Vector2& _rV2);

  float Angle(const Vector2& _rOther) const;
  static float Angle(const Vector2& _rV1, const Vector2& _rV2);

  float Distance(const Vector2& _rOther) const;
  static float Distance(const Vector2& _rV1, const Vector2& _rV2);

  float Length() const;
  static float Length(const Vector2& _rVector);

  bool IsNormalized() const;
  void Normalize();

private:

  // Atributos -----------------------------------

  float m_fX;
  float m_fY;
};

ENGINE_API Vector2 operator+(const Vector2& _rVector, float _fScalar);
ENGINE_API Vector2 operator-(const Vector2& _rVector, float _fScalar);
ENGINE_API Vector2 operator*(const Vector2& _rVector, float _fScalar);
ENGINE_API Vector2 operator/(const Vector2& _rVector, float _fScalar);