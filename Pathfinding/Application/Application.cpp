
#include "Engine/Render/RenderEngine.h"
#include "Engine/DrawUtilities/Grid.h"
#include "Pathfinding/WorldGenerator.h"

int main()
{
  CRenderEngine::Init();

  Pathfinding::CWorldGenerator world(Pathfinding::Vec2(100, 90));
  world.Init(Pathfinding::Vec2(0, 0), Pathfinding::Vec2(56, 87));

  while (CRenderEngine::Get().IsWindowRunning())
  {
    world.PathfindingSlot();
    CRenderEngine::Get().Update();
  }

  CRenderEngine::Terminate();
  return 0;
}