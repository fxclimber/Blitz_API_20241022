#pragma once
#include <Windows.h>
#include <assert.h>


//#define MSGASSERT(VALUE) MessageBoxA(nullptr, VALUE, "ġ���� ����", MB_OK); assert(false);

#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK); assert(false);