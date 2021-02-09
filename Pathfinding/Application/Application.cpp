
#include "Engine/Render/RenderEngine.h"
#include "Engine/Timer/TimeManager.h"
#include "Pathfinding/PathSolver.h"

int main()
{
  CRenderEngine::Init();
  CTimeManager::Init();

  Pathfinding::CPathSolver pathSolver;
  pathSolver.Init(CMap::LoadMap("GeneratedMap.txt"), Pathfinding::Vec2(0, 0), Pathfinding::Vec2(99, 99));

  while (CRenderEngine::Get().IsWindowRunning())
  {
    pathSolver.PathfindingSlot();
    CRenderEngine::Get().Update();
  }
  pathSolver.Shutdown();
  CTimeManager::Shutdown();
  CRenderEngine::Terminate();
  return 0;
}