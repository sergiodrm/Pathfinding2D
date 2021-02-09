
#include <cstdio>
#include "Engine/Render/RenderEngine.h"
#include "Engine/Input/InputManager.h"
#include "MapGenerator/MapGenerator.h"

int main()
{
  CRenderEngine::Init();
  CInputManager::Init();

  CMapGenerator mapGenerator;
  mapGenerator.Init(100, 100);


  while (CRenderEngine::Get().IsWindowRunning())
  {
    CInputManager::GetInstance().Update();
    mapGenerator.Update();
    CRenderEngine::Get().Update();
  }
  mapGenerator.SaveMap("GeneratedMap.txt");
  mapGenerator.Shutdown();
  CInputManager::Shutdown();
  CRenderEngine::Terminate();

  return 0;
}