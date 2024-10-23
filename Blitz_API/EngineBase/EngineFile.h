#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>


const int MAXPATH = 256;

class UEngineFile
{
// 하드코딩 
public:
	UEngineFile();
	~UEngineFile();

	inline void SetPath(const char* _Path)
	{
		strcpy_s(Path, _Path);
	}


	// Write
	void Write(const void* _Ptr, size_t _Size);
	void Read(void* _Ptr, size_t _Size);

	void FileOpen(const char* _Mode);
	bool IsExits();
	void Close();

// 기능 클래스 랩핑
private:
	// 상수
	// _MAX_DIR 윈도우에 의존적인 프로그램
	

	char Path[MAXPATH] = "";
	FILE* File = nullptr;
};

