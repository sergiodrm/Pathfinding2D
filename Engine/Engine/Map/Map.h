#pragma once

#include <vector>
#include "Engine/MacroObject.h"

class ENGINE_API CMap
{
public:

  explicit CMap();
  explicit CMap(size_t _numOfRows, size_t _numOfCols);

  bool GetCellState(size_t _row, size_t _col) const;
  void SetCellState(size_t _row, size_t _col, bool _bState);

  static CMap CreateMap(const char* _sCollisionMap);
  static CMap LoadMap(const char* _sFilename);
  static void SaveMap(const char* _sFilename, const CMap& _map);

private:

  size_t RC2Index(size_t _row, size_t _col) const;
  void Index2RC(size_t _index, size_t& row_, size_t& col_) const;

private:

  std::vector<bool> m_wallsMap;
  size_t m_numberOfRows;
  size_t m_numberOfColumns;
};

