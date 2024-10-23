#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClass;

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    //��Ƽ����Ʈ ���������� ����Ұ��̹Ƿ�, �ڿ� A���� �Լ� ���!
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

	hInstance = _Instance;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClass.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClass.find(std::string(_Class.lpszClassName));

    if (EndIter != FindIter)
    {
        MSGASSERT("���� �̸��� ������ Ŭ������ 2�� ���" + std::string(_Class.lpszClassName));
        return;
    }
    RegisterClassExA(&_Class);

    WindowClass.insert(std::pair{ _Class.lpszClassName, _Class });
}

//bool UEngineWindow::IsWindowClass(const std::string_view _text)
//{
//}

int UEngineWindow::WindowMessageLoop()
{
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
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
        MSGASSERT("����������� Ŭ������ ������â�� ������� �߽��ϴ�" + std::string(_ClassName));
        return;
    }
    WindowHandle = CreateWindowA(_ClassName.data(),_TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!WindowHandle)
    {
        MSGASSERT("������ ������ �����߽��ϴ�" + std::string(_TitleName));
        return;
    }

}

void UEngineWindow::Create(std::string_view _ClassName)
{
    Create("Window", _ClassName);
}

void UEngineWindow::Open(std::string_view _TitleName)
{
    if (nullptr == WindowHandle)
    {
        Create();
    }
    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);

}



