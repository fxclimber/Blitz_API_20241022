#pragma once
//os header
#include <Windows.h>

//std header
#include <map>
#include <string>
#include <functional>

//user header
#include <EngineBase/EngineDelegate.h>
#include "EngineInput.h"

class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	UEngineWindow();
	~UEngineWindow();

	//delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other)noexcept = delete;

	//void Open();      
	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");

	inline HDC GetBackBuffer()
	{
		return BackBuffer;
	}

	inline void SetWindowTitle(std::string_view Text)
	{
		// �����Լ��� �ƴ϶� ����Ƽ�� �Լ���� �Ѵ�
		// C++ �� ����� �Լ�
		SetWindowTextA(WindowHandle, Text.data());
	}

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClass;
	//1��
	HWND WindowHandle = nullptr;
	HDC BackBuffer = nullptr;



};

