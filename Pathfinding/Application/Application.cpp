
#include "Engine/Render/RenderEngine.h"
#include "Engine/DrawUtilities/Grid.h"
#include "Pathfinding/PathSolver.h"

int main()
{
  CRenderEngine::Init();

  Pathfinding::CPathSolver world(Pathfinding::Vec2(50, 50));
  world.Init(Pathfinding::Vec2(0, 0), Pathfinding::Vec2(1, 42));

  while (CRenderEngine::Get().IsWindowRunning())
  {
    world.PathfindingSlot();
    CRenderEngine::Get().Update();
  }

  CRenderEngine::Terminate();
  return 0;
}