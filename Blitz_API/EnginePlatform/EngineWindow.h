#pragma once
#include <Windows.h>
#include <string>
#include <map>

class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	static bool IsWindowClass(const std::string_view _text);

	static int WindowMessageLoop();

	UEngineWindow();
	~UEngineWindow();

	//delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other)noexcept = delete;

	//void Open();
	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Create(std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");


protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClass;
	//1°³
	HWND WindowHandle = nullptr;




};

