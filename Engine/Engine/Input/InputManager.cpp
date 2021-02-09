#include "InputManager.h"
#include "Engine/ExternalLibs/glfw3.h"
#include "Engine/Render/RenderEngine.h"
#include "Engine/CoreUtilities/KeyCodes.h"

std::map<int, CInputManager::SKeyStatus> CInputManager::m_keyStatus;

void CInputManager::Init()
{
  CreateSingleton();
  GetSingleton().Init_Internal();
}

CInputManager& CInputManager::GetInstance()
{
  return GetSingleton();
}

void CInputManager::Shutdown()
{
  DestroySingleton();
}

void CInputManager::Broadcast()
{
  for (auto& iterator : m_keyStatus)
  {
    if (iterator.second.m_bLastFrame != iterator.second.m_bCurrentFrame)
    {
      if (iterator.first >= KEYBOARD_A && iterator.first <= KEYBOARD_Z)
      { 
        m_keyboardDispatcher.Broadcast(iterator.first, iterator.second.m_bCurrentFrame ? PRESSED : RELEASED);
      }
      else m_mouseButtonDispatcher.Broadcast(iterator.first, iterator.second.m_bCurrentFrame ? PRESSED : RELEASED);
      iterator.second.m_bLastFrame = iterator.second.m_bCurrentFrame;
    }
  }
}

void CInputManager::UpdateKeyStatus()
{
}

void CInputManager::Update()
{
  Broadcast();
  UpdateKeyStatus();
}

void CInputManager::KeyboardCallback(GLFWwindow* _pWindow, int _key, int _scanCode, int _action, int _mode)
{
  std::map<int, SKeyStatus>::iterator item = m_keyStatus.find(_key);
  item->second.m_bCurrentFrame = _action == GLFW_PRESS;
}

void CInputManager::MouseCallback(GLFWwindow* _pWindow, int _button, int _action, int _mod)
{
  std::map<int, SKeyStatus>::iterator item = m_keyStatus.find(_button);
  item->second.m_bCurrentFrame = _action == GLFW_PRESS;
}

void CInputManager::Init_Internal()
{
  glfwSetKeyCallback(CRenderEngine::Get().GetWindow(), &KeyboardCallback);
  glfwSetMouseButtonCallback(CRenderEngine::Get().GetWindow(), &MouseCallback);

  m_keyStatus.clear();
  for (int key = KEYBOARD_A; key <= KEYBOARD_Z; ++key)
  {
    m_keyStatus.insert(std::make_pair(key, SKeyStatus()));
  }
  m_keyStatus.insert(std::make_pair(KEYBOARD_SPACE, SKeyStatus()));
  m_keyStatus.insert(std::make_pair(MOUSE_BUTTON_LEFT, SKeyStatus()));
  m_keyStatus.insert(std::make_pair(MOUSE_BUTTON_MIDDLE, SKeyStatus()));
  m_keyStatus.insert(std::make_pair(MOUSE_BUTTON_RIGHT, SKeyStatus()));
}

void CInputManager::Shutdown_Internal()
{
  
}
