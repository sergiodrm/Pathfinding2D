
#include <cstdio>
#include "Engine/Render/RenderEngine.h"
#include "Engine/Map/Map.h"

int main()
{
  /*CRenderEngine::Init();

  while (CRenderEngine::Get().IsWindowRunning())
  {

    CRenderEngine::Get().Update();
  }

  CRenderEngine::Terminate();*/

  CMap loadedMap = CMap::LoadMap("Map1.txt");
  CMap::SaveMap("Map2.txt", loadedMap);

  return 0;
}