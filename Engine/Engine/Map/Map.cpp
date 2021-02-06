#include "Map.h"
#include "Engine/MacroObject.h"
#include "Engine/FileSystem/MapSaver.h"


CMap::CMap(size_t _numOfRows, size_t _numOfCols)
  : Super(_numOfRows, _numOfCols),
  m_wallsMap(), m_bUpdatedMap(false)
{}

bool CMap::GetCellState(size_t _row, size_t _col) const 
{
  size_t index = RC2Index(_row, _col);
  return m_wallsMap[index];
}

void CMap::SetCellState(size_t _row, size_t _col, bool _bState) 
{
  size_t index = RC2Index(_row, _col);
  m_wallsMap[index] = _bState;
  m_bUpdatedMap = true;
}


CMap* CMap::CreateMap(const char* _sCollisionMap)
{
  ensure(_sCollisionMap != nullptr);
  size_t index = 0;
  size_t rows = 1;
  size_t cols = 0;
  std::vector<bool> collisions;
  while (_sCollisionMap[index] != '\0')
  {
    switch (_sCollisionMap[index])
    {
    case '0':
      collisions.push_back(false);
      break;
    case '1':
      collisions.push_back(true);
      break;
    case '\n':
      if (cols == 0)
        cols = index;
      ++rows;
    }
    ++index;
  }
  if (_sCollisionMap[index -1 ] == '\n') --rows;
  CMap* collisionMap = new CMap(rows, cols);
  collisionMap->m_wallsMap = collisions;
  collisionMap->RenderMap();
  return collisionMap;
}

CMap* CMap::LoadMap(const char* _sFilename)
{
  ensure(_sFilename != nullptr);
  std::string stringMap = MapSaveSystem::LoadMap(_sFilename);
  return CreateMap(stringMap.c_str());
}

void CMap::SaveMap(const char* _sFilename, const CMap& _map)
{
  ensure(_sFilename != nullptr);
  std::string content;
  for (size_t index = 0; index < _map.m_wallsMap.size(); ++index)
  {
    content.push_back(_map.m_wallsMap[index] ? '1' : '0');
    if (index % _map.m_numberOfColumns == _map.m_numberOfColumns - 1)
      content.push_back('\n');
  }
  MapSaveSystem::SaveMap(_sFilename, content.c_str());
}

void CMap::DestroyMap(CMap* _pMap)
{
  delete _pMap;
}

void CMap::Draw_Internal(const Vector2& _screenSize)
{
  if (m_bUpdatedMap)
    RenderMap();
  Super::Draw_Internal(_screenSize);
}

void CMap::RenderMap()
{
  float color[] = { NORMALIZE_RGB(27), NORMALIZE_RGB(79), NORMALIZE_RGB(114), 1.f };
  for (size_t index = 0; index < m_wallsMap.size(); ++index)
  {
    if (m_wallsMap[index])
    {
      size_t row, col;
      Index2RC(index, row, col);
      Super::ActiveRectangle(row, col);
      Super::SetRectangleColor(row, col, color);
    }
  }
  m_bUpdatedMap = false;
}

