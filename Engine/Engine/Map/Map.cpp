#include "Map.h"
#include "Engine/MacroObject.h"
#include "Engine/FileSystem/MapSaver.h"


CMap::CMap()
  : m_wallsMap(), m_numberOfRows(0), m_numberOfColumns(0)
{}

CMap::CMap(size_t _numOfRows, size_t _numOfCols)
  : m_wallsMap(), m_numberOfRows(0), m_numberOfColumns(0) 
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
}

CMap CMap::CreateMap(const char* _sCollisionMap)
{
  ensure(_sCollisionMap != nullptr);
  size_t index = 0;
  size_t rows = 1;
  size_t cols = 0;
  CMap collisionMap;
  while (_sCollisionMap[index] != '\0')
  {
    switch (_sCollisionMap[index])
    {
    case '0':
      collisionMap.m_wallsMap.push_back(false);
      break;
    case '1':
      collisionMap.m_wallsMap.push_back(true);
      break;
    case '\n':
      if (cols == 0)
        cols = index;
      ++rows;
    }
    ++index;
  }
  collisionMap.m_numberOfColumns = cols;
  collisionMap.m_numberOfRows = rows;
  return collisionMap;
}

CMap CMap::LoadMap(const char* _sFilename)
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

size_t CMap::RC2Index(size_t _row, size_t _col) const
{
  return _row * m_numberOfColumns + _col;
}

void CMap::Index2RC(size_t _index, size_t& row_, size_t& col_) const
{
  row_ = _index / m_numberOfColumns;
  col_ = _index % m_numberOfColumns;
}
