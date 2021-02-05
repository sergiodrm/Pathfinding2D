#include "FileStream.h"
#include "Engine/MacroObject.h"

CFileStream::CFileStream()
: m_inputStream(), m_outputStream()
{}

void CFileStream::OpenFile(const char* _sFilename, EModes _eOpenMode)
{
  ensure(_sFilename != nullptr);
  if (!m_inputStream.is_open() && !m_outputStream.is_open())
  {
    switch (_eOpenMode)
    {
    case CFileStream::Read:
      m_inputStream.open(_sFilename, std::ios::in);
      if (!m_inputStream.is_open())
        PRINT_WARNING("%s not found.", _sFilename);
      break;
    case CFileStream::Write:
      m_outputStream.open(_sFilename, std::ios::out);
      if (!m_outputStream.is_open())
        PRINT_WARNING("%s not found.", _sFilename);
      break;
    default:
      PRINT_WARNING("Open mode invalid.");
    }
  }
  else
  {
    PRINT_WARNING("Stream is already open!");
  }
}

void CFileStream::CloseFile()
{
  if (m_inputStream.is_open())
  {
    m_inputStream.close();
  }
  else if (m_outputStream.is_open())
  {
    m_outputStream.close();
  }
}

std::string CFileStream::ReadAll()
{
  if (m_inputStream.is_open())
  {
    m_inputStream.seekg(0, m_inputStream.end);
    int fileSize = m_inputStream.tellg();
    m_inputStream.seekg(0, m_inputStream.beg);
    char* sInfo = new char[fileSize];
    m_inputStream.read(sInfo, fileSize);
    std::string content = sInfo;
    delete sInfo;
    return content;
  }
  PRINT_WARNING("Stream is not open.");
  return std::string();
}

std::string CFileStream::ReadFile(unsigned int _n)
{
  if (m_inputStream.is_open())
  {
    std::string content;
    unsigned int numberRead = 0;
    char* sInfo = new char[_n + 1];
    m_inputStream.get(sInfo, _n);
    content = sInfo;
    delete sInfo;
    return content;
  }
  PRINT_WARNING("Stream is not open.");
  return std::string();
}

void CFileStream::WriteFile(const char* _sString)
{
  ensure_msg(_sString != nullptr, "Null pointer is an invalid string.");
  if (m_outputStream.is_open())
  {
    m_outputStream.write(_sString, strlen(_sString));
  }
  else PRINT_WARNING("Stream is not open.");
}
