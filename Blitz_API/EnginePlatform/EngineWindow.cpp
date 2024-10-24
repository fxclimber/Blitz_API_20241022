#include "PreCompiledFile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClass;
int WindowCount = 0;

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
	
    hInstance = _Instance;

    //멀티바이트 문자집합을 사용할것이므로, 뒤에 A붙은 함수 사용!
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;

    CreateWindowClass(wcex);

}
int UEngineWindow::WindowMessageLoop(EngineDelegate _FrameFunction)
{
	MSG msg;

	while (WindowCount)
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        //메세지 처리후 게임엔진을 돌린다.엔진api코어의 tick,render에서 

        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
        // 메세지가 없는 시간에 내 게임을 돌리는거야.
        // 메세지 처리하고 나서 내 게임엔진을 돌린다.

	}
	return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClass.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClass.find(std::string(_Class.lpszClassName));

    if (EndIter != FindIter)
    {
        MSGASSERT("같은 이름의 윈도우 클래스를 2번 등록" + std::string(_Class.lpszClassName));
        return;
    }
    RegisterClassExA(&_Class);

    WindowClass.insert(std::pair{ _Class.lpszClassName, _Class });
}



UEngineWindow::UEngineWindow()
{
    HWND WindowHandle = nullptr;




    if (!WindowHandle)
    {
        return;
    }
}

UEngineWindow::~UEngineWindow()
{
}


void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClass.contains(_ClassName.data()))
    {
        MSGASSERT("등록하지않은 클래스로 윈도우창을 만들려고 했습니다" + std::string(_ClassName));
        return;
    }
    WindowHandle = CreateWindowA(_ClassName.data(),_TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!WindowHandle)
    {
        MSGASSERT("윈도우 생성에 실패했습니다" + std::string(_TitleName));
        return;
    }

}

void UEngineWindow::Open(std::string_view _TitleName)
{
    if (nullptr == WindowHandle)
    {
        Create("Window");
    }
    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
}



