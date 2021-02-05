
#include <cstdio>
#include "Engine/Render/RenderEngine.h"

int main()
{
  CRenderEngine::Init();

  while (CRenderEngine::Get().IsWindowRunning())
  {

    CRenderEngine::Get().Update();
  }

  CRenderEngine::Terminate();

  return 0;
}