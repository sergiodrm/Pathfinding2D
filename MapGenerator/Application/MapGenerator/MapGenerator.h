#pragma once

class CMap;
class Vector2;

class CMapGenerator
{
public:

  CMapGenerator();

  void Init(size_t _numOfRows, size_t _numOfCols);
  void Update();
  void Shutdown();

  void SaveMap(const char* _sFilename);

  void MouseButtonCallback(int _button, int _action);

private:

  void WorldPosition2CellGrid(const Vector2& _position, size_t& row_, size_t& col_) const;

  CMap* m_map;
  bool m_bDrawing;

};

