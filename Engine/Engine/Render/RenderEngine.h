#pragma once

#include "../CoreUtilities/SingletonBase.h"
#include "../Math/Vector2.h"
#include <vector>

// Forward declaration
struct GLFWwindow;

// Callback draw function declaration
typedef void (*ExternalDrawFunction)(void*, const Vector2&);
// Callback for mouse input
typedef void (*MouseInputCallback)(int, int, const Vector2&);

class ENGINE_API CRenderEngine : public ISingletonBase<CRenderEngine>
{
  DECLARE_SINGLETON_CLASS(CRenderEngine)

  /**
  *     Properties
  */
  GLFWwindow* m_pWindow;
  std::vector<std::pair<void*, ExternalDrawFunction>> m_externalDrawFunctions;

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

  void InsertExternalDrawFunction(void* _pInstance, ExternalDrawFunction _pCallback);

  /**
  *     Set callbacks
  */
  void SetMouseInputCallback(MouseInputCallback _pCallback);

  /**
  *     Draw functions
  */
  static void SetColor(float _fGrey);
  static void SetColor(float _fR, float _fG, float _fB);
  static void DrawLine(const Vector2& _origin, const Vector2 _destiny);
  static void DrawRectangle(const Vector2& _position, const Vector2& _size);

private:

  void Init_Internal();
  void Terminate_Internal();
  void ProcessDrawFunctions();

};

