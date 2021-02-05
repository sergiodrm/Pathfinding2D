
#include "Engine/Render/RenderEngine.h"
#include "Engine/Timer/TimeManager.h"
#include "Pathfinding/PathSolver.h"

int main()
{
  CRenderEngine::Init();
  CTimeManager::Init();

  Pathfinding::CPathSolver world(Pathfinding::Vec2(200, 200));
  world.Init(Pathfinding::Vec2(0, 0), Pathfinding::Vec2(150, 172));

  while (CRenderEngine::Get().IsWindowRunning())
  {
    world.PathfindingSlot();
    CRenderEngine::Get().Update();
  }

  CTimeManager::Shutdown();
  CRenderEngine::Terminate();
  return 0;
}