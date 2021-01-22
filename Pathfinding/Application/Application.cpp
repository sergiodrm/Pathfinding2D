
#include "Engine/Render/RenderEngine.h"
#include "Engine/DrawUtilities/Grid.h"

int main()
{
  CRenderEngine::Init();

  CGrid oGrid(10, 10);
  oGrid.Activate();

  while (CRenderEngine::Get().IsWindowRunning())
  {
    CRenderEngine::Get().Update();
  }

  CRenderEngine::Terminate();
  return 0;
}