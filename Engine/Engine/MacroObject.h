#pragma once


#ifdef _ENGINE_BUILD_DLL

#define API_ENGINE __declspec(dllexport)

#else

#define API_ENGINE __declspec(dllimport)

#endif // _ENGINE_DEFINITION
