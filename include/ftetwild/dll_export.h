#pragma once
#ifdef _WIN32
#ifdef FLOAT_TETWILD_EXPORT_DLL
#define FLOAT_TETWILD_API __declspec(dllexport)
#else
#define FLOAT_TETWILD_API __declspec(dllimport)
#endif
#else
#define FLOAT_TETWILD_API
#endif