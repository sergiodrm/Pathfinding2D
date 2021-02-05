#pragma once
#include <string>
#include "Engine/MacroObject.h"

namespace MapSaveSystem
{
  bool ENGINE_API SaveMap(const char* _sFilename, const char* _sMap);
  std::string ENGINE_API LoadMap(const char* _sFilename);
}
