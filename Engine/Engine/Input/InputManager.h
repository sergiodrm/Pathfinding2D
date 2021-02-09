#pragma once

#include <functional>
#include <map>

#include "Engine/CoreUtilities/SingletonBase.h"
#include "Engine/EventSystem/Dispatcher/Dispatcher.h"
#include "Engine/ExternalLibs/glfw3.h"
#include "Engine/Math/Vector2.h"

class ENGINE_API CInputManager : public ISingletonBase<CInputManager>
{
  DECLARE_SINGLETON_CLASS(CInputManager);

  struct SKeyStatus
  {
    bool m_bLastFrame;
    bool m_bCurrentFrame;
    SKeyStatus(bool _bCurrent = false, bool _bLast = false)
      : m_bCurrentFrame(_bCurrent), m_bLastFrame(_bLast) {}
  };

public:


public:

  static void Init();
  static CInputManager& GetInstance();
  static void Shutdown();

  template <typename T, void(T::*M)(int, int)>
  void BindKeyboardCallback(T* _pInstance);

  template <typename T, void(T::* M)(int, int)>
  void BindMouseButtonCallback(T* _pInstance);

  void Update();

  static void KeyboardCallback(GLFWwindow* _pWindow, int _key, int _scanCode, int _action, int _mode);
  static void MouseCallback(GLFWwindow* _pWindow, int _button, int _action, int _mod);

private:

  void Broadcast();
  void UpdateKeyStatus();
  void Init_Internal();
  void Shutdown_Internal();

  Dispatcher<int, int> m_keyboardDispatcher;
  Dispatcher<int, int> m_mouseButtonDispatcher;

  static std::map<int, SKeyStatus> m_keyStatus;

};

/**
 * Templates definition
 */

template <typename T, void(T::* M)(int, int)>
void CInputManager::BindKeyboardCallback(T* _pInstance)
{
  m_keyboardDispatcher.Bind<T, M>(_pInstance);
}

template <typename T, void(T::* M)(int, int)>
void CInputManager::BindMouseButtonCallback(T* _pInstance)
{
  m_mouseButtonDispatcher.Bind<T, M>(_pInstance);
}
