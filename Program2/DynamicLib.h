#pragma once
#include <iostream>

#ifdef DYNAMICLIB_EXPORTS
#define DYNAMICLIB_API __declspec(dllexport)
#else
#define DYNAMICLIB_API __declspec(dllimport)
#endif

extern "C" DYNAMICLIB_API void insertKB(std::string& str);

extern "C" DYNAMICLIB_API int sumString(const std::string str);

extern "C" DYNAMICLIB_API bool stringLength(const std::string str);