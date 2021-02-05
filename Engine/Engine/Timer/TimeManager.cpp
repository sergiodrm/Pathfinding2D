#include "TimeManager.h"
#include "Engine/ExternalLibs/glfw3.h"

void CTimeManager::Init()
{
  CreateSingleton();
}

CTimeManager& CTimeManager::GetInstance()
{
  return GetSingleton();
}

void CTimeManager::Shutdown()
{
  DestroySingleton();
}

void CTimeManager::StartTimer()
{
  m_timer = glfwGetTime();
}

double CTimeManager::StopTimer()
{
  return glfwGetTime() - m_timer;
}
