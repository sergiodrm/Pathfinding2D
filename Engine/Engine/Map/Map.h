#pragma once

#include <vector>
#include "Engine/MacroObject.h"
#include "Engine/DrawUtilities/Grid.h"

class ENGINE_API CMap : public CGrid
{
public:


  bool GetCellState(size_t _row, size_t _col) const;
  void SetCellState(size_t _row, size_t _col, bool _bState);


  static CMap* CreateMap(const char* _sCollisionMap);
  static CMap* LoadMap(const char* _sFilename);
  static void SaveMap(const char* _sFilename, const CMap& _map);
  static void DestroyMap(CMap* _pMap);


protected:
  explicit CMap(size_t _numOfRows = 0, size_t _numOfCols = 0);

  virtual void Draw_Internal(const Vector2& _screenSize) override;
  void RenderMap();

private:

  std::vector<bool> m_wallsMap;
  bool m_bUpdatedMap;
};


