#include "RenderEngine.h"
#include "Engine/ExternalLibs/glfw3.h"
#include "Engine/MacroObject.h"

#define LITE_GFX_IMPLEMENTATION
#include "../ExternalLibs/litegfx.h"
#undef LITE_GFX_IMPLEMENTATION

void CRenderEngine::Init()
{
  CreateSingleton();
  GetSingleton().Init_Internal();
}

CRenderEngine& CRenderEngine::Get()
{
  return GetSingleton();
}

void CRenderEngine::Terminate()
{
  GetSingleton().Terminate_Internal();
  DestroySingleton();
}

bool CRenderEngine::IsWindowRunning() const
{
  return !glfwWindowShouldClose(m_pWindow);
}

void CRenderEngine::Update()
{
  lgfx_clearcolorbuffer(0.1f, 0.1f, 0.1f);

  ProcessDrawFunctions();

  glfwSwapBuffers(m_pWindow);
  glfwPollEvents();
}

Vector2 CRenderEngine::GetWindowSize() const
{
  int iWidth, iHeight;
  glfwGetWindowSize(m_pWindow, &iWidth, &iHeight);
  return Vector2(static_cast<float>(iWidth), static_cast<float>(iHeight));
}

void CRenderEngine::InsertExternalDrawFunction(void* _pInstance, ExternalDrawFunction _pCallback)
{
  ensure(_pInstance != nullptr && _pCallback != nullptr);
  m_externalDrawFunctions.push_back(std::pair<void*, ExternalDrawFunction>(_pInstance, _pCallback));
}

void CRenderEngine::SetMouseInputCallback(MouseInputCallback _pCallback)
{
  
}

void CRenderEngine::SetColor(float _fGrey)
{
  lgfx_setcolor(_fGrey, _fGrey, _fGrey, 1.f);
}

void CRenderEngine::SetColor(float _fR, float _fG, float _fB)
{
  lgfx_setcolor(_fR, _fG, _fB, 1.f);
}

void CRenderEngine::DrawLine(const Vector2& _origin, const Vector2 _destiny)
{
  lgfx_drawline(_origin.GetX(), _origin.GetY(), _destiny.GetX(), _destiny.GetY());
}

void CRenderEngine::DrawRectangle(const Vector2& _position, const Vector2& _size)
{
  lgfx_drawrect(_position.GetX(), _position.GetY(), _size.GetX(), _size.GetY());
}

void CRenderEngine::Init_Internal()
{
  PRINT_LOG("Render initialization...");
  {
    int iRenderStatus = glfwInit();
    ensure_msg(iRenderStatus == GLFW_TRUE, "Render failed (glfwInit)");
  }
  m_pWindow = glfwCreateWindow(1024, 720, "Pathfinding project", nullptr, nullptr);
  ensure_msg(m_pWindow != nullptr, "Window creation failed");
  glfwMakeContextCurrent(m_pWindow);
  lgfx_setup2d(1024, 720);
  PRINT_LOG("Render inits successfuly");
}

void CRenderEngine::Terminate_Internal()
{
  glfwTerminate();
}

void CRenderEngine::ProcessDrawFunctions()
{
  Vector2 screenSize(GetWindowSize());
  for (const std::pair<void*, ExternalDrawFunction>& iterator : m_externalDrawFunctions)
  {
    ensure(iterator.first != nullptr && iterator.second != nullptr);
    iterator.second(iterator.first, screenSize);
  }
}
