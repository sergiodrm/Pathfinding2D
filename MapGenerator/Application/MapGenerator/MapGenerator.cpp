#include "MapGenerator.h"

#include <string>

#include "Engine/Map/Map.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Render/RenderEngine.h"
#include "Engine/CoreUtilities/KeyCodes.h"

CMapGenerator::CMapGenerator()
  : m_map(nullptr), m_bDrawing(false) {}

void CMapGenerator::Init(size_t _numOfRows, size_t _numOfCols)
{
  std::string collisionMap;
  for (int index = 0; index < _numOfCols * _numOfRows; ++index)
  {
    collisionMap.push_back('0');
    if (index % static_cast<int>(_numOfCols) == static_cast<int>(_numOfCols) - 1)
      collisionMap.push_back('\n');
  }
  m_map = CMap::CreateMap(collisionMap.c_str());
  CInputManager::GetInstance().BindMouseButtonCallback<CMapGenerator, &CMapGenerator::MouseButtonCallback>(this);
}

void CMapGenerator::Update()
{
  if (m_bDrawing)
  {
    size_t mouseRow, mouseCol;
    WorldPosition2CellGrid(CRenderEngine::Get().GetMousePosition(), mouseRow, mouseCol);
    m_map->SetCellState(mouseRow, mouseCol, true);
  }
}

void CMapGenerator::Shutdown()
{
  CMap::DestroyMap(m_map);
}

void CMapGenerator::SaveMap(const char* _sFilename)
{
  CMap::SaveMap(_sFilename, *m_map);
}

void CMapGenerator::MouseButtonCallback(int _button, int _action)
{
  if (_button == MOUSE_BUTTON_LEFT)
  {
    m_bDrawing = _action == PRESSED;
  }
}

void CMapGenerator::WorldPosition2CellGrid(const Vector2& _position, size_t& row_, size_t& col_) const
{
  Vector2 screenSize = CRenderEngine::Get().GetWindowSize();
  float deltaRow = screenSize.GetY() / static_cast<float>(m_map->GetNumOfRows());
  float deltaCol = screenSize.GetX() / static_cast<float>(m_map->GetNumOfColumns());

  row_ = static_cast<size_t>(_position.GetY() / deltaRow);
  col_ = static_cast<size_t>(_position.GetX() / deltaCol);
}
