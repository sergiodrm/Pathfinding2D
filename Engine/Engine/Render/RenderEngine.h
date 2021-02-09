#pragma once

#include "Engine/CoreUtilities/SingletonBase.h"
#include "Engine/Math/Vector2.h"
#include "Engine/EventSystem/Dispatcher/Dispatcher.h"
#include <vector>

// Forward declaration
struct GLFWwindow;


class ENGINE_API CRenderEngine : public ISingletonBase<CRenderEngine>
{
  DECLARE_SINGLETON_CLASS(CRenderEngine)


public:

  /**
  *     Singleton interface
  */
  static void Init();
  static CRenderEngine& Get();
  static void Terminate();

  /**
  *     API
  */
  bool IsWindowRunning() const;
  void Update();
  Vector2 GetWindowSize() const;
  GLFWwindow* GetWindow() const;
  Vector2 GetMousePosition() const;

  template <typename T, void(T::*M)(const Vector2&)>
  void BindExternalDrawDelegate(void* _pInstance);
  template <typename T, void(T::* M)(const Vector2&) const>
  void BindExternalDrawDelegate(void* _pInstance);

  /**
  *     Draw functions
  */
  static void SetColor(float _fGrey);
  static void SetColor(float _fR, float _fG, float _fB);
  static void DrawLine(const Vector2& _origin, const Vector2& _destiny);
  static void DrawRectangle(const Vector2& _position, const Vector2& _size);
  static void DrawCircle(const Vector2& _position, const Vector2& _size);

private:

  void Init_Internal();
  void Terminate_Internal();
  void ProcessDrawFunctions();

private:
  /**
  *     Properties
  */
  Dispatcher<const Vector2&> m_externalDrawDispatcher;
  GLFWwindow* m_pWindow;
};

/**
 * Template definition
 */
template <typename T, void(T::* M)(const Vector2&)>
void CRenderEngine::BindExternalDrawDelegate(void* _pInstance)
{
  m_externalDrawDispatcher.Bind<T, M>(_pInstance);
}
template <typename T, void(T::* M)(const Vector2&) const>
void CRenderEngine::BindExternalDrawDelegate(void* _pInstance)
{
  m_externalDrawDispatcher.Bind<T, M>(_pInstance);
}
