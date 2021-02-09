
#include "MapSaver.h"
#include "FileStream.h"

bool MapSaveSystem::SaveMap(const char* _sFilename, const char* _sMap)
{
  if (_sFilename != nullptr && _sMap != nullptr)
  {
    CFileStream file;
    file.OpenFile(_sFilename, CFileStream::Write);
    std::string contentToSave;
    contentToSave += "<version=\"1.0\"/>\n";
    contentToSave += "<name=\"";
    contentToSave += _sFilename;
    contentToSave += "\"/>\n";
    contentToSave += "<map>\n";
    contentToSave += _sMap;
    contentToSave += "\n</map>\n";
    file.WriteFile(contentToSave.c_str());
    file.CloseFile();
    return true;
  }
  PRINT_WARNING("Invalid input to save map.");
  return false;
}

std::string MapSaveSystem::LoadMap(const char* _sFilename)
{
  if (_sFilename != nullptr)
  {
    CFileStream fileStream;
    fileStream.OpenFile(_sFilename, CFileStream::Read);
    std::string content(fileStream.ReadAll());
    fileStream.CloseFile();
    size_t mapPosition = content.find("<map>");
    size_t endMapPosition = content.find("\n</map>");
    if (mapPosition != std::string::npos && endMapPosition != std::string::npos)
    {
      std::string map(content.substr(mapPosition + 6, endMapPosition - (mapPosition + 7)));
      map.shrink_to_fit();
      return map;
    }
  }
  PRINT_WARNING("Invalid input to load map.");
  return std::string();
}
