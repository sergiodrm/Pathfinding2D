#pragma once

#include "Engine/MacroObject.h"
#include <string>
#include <fstream>

class ENGINE_API CFileStream
{
public:

  enum EModes
  {
    Invalid = -1,
    Read, Write
  };

public:

  CFileStream();

  void OpenFile(const char* _sFilename, EModes _eOpenMode);
  void CloseFile();

  std::string ReadAll();
  std::string ReadFile(unsigned int _n);
  void WriteFile(const char* _sString);

private:

  std::ifstream m_inputStream;
  std::ofstream m_outputStream;

};

