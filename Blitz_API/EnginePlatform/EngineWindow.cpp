#include "PreCompiledFile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>


HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClass;
int WindowCount = 0;


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

}

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
	MSG msg = MSG();//�����쿡 ����?�� ������ �޼��� ����

    if (true == _StartFunction.IsBind())
    {
        _StartFunction();//��������Ʈ �Լ�����Ʈ�� ����������(�ִ�.����,����2��) �Լ�ȣ��
    }

	while (0 != WindowCount)//������������,����? �ھ�� ����� ���������,
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        //�޼��� ó���� ���ӿ����� ������.����api�ھ��� tick,render���� 

        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
        // �޼����� ���� �ð��� �� ������ �����°ž�.
        // �޼��� ó���ϰ� ���� �� ���ӿ����� ������.

	}
    //Ű����,���콺�� �Է��� ������ ĳ����(int)�ؼ�, ���α׷����Ḧ ȣ���ڿ��� �˸�. 
	return (int)msg.wParam;
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

UEngineWindow::UEngineWindow()
{
}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    // Ŭ�����̸��� �߿��ϴ�.
    // _ClassName�� ����Ÿ�� contains�ƴϸ�,
    if (false == WindowClass.contains(_ClassName.data()))
    {
        MSGASSERT("����������� Ŭ������ ������â�� ������� �߽��ϴ�" + std::string(_ClassName));
        return;
    }

    //WindowHandle = CreateWindowA(_ClassName.data(),_TitleName.data(), WS_OVERLAPPEDWINDOW,
    //    0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    // HWND �������ڵ��� ����.
    WindowHandle = CreateWindowA(
        _ClassName.data(),   // ������ Ŭ���� �̸� (��ϵ� Ŭ������)
        _TitleName.data(),   // ������ ����
        WS_OVERLAPPEDWINDOW, // ������ ��Ÿ�� (Ÿ��Ʋ��, �ִ�ȭ, �ּ�ȭ ��ư ����)
        0,                   // �������� �ʱ� x ��ġ
        0,                   // �������� �ʱ� y ��ġ
        CW_USEDEFAULT,       // �⺻ �ʺ� ����
        0,                   // �⺻ ���̸� ���� (CW_USEDEFAULT�� ���� ����)
        nullptr,             // �θ� ������ �ڵ� (���ٸ� nullptr)
        nullptr,             // �޴� �ڵ� (���ٸ� nullptr)
        hInstance,           // ���� ���ø����̼� �ν��Ͻ� �ڵ�
        nullptr              // �߰� �Ű����� (�ʿ� ������ nullptr)
    );


    if ( nullptr == WindowHandle)
    {
        MSGASSERT("������ ������ �����߽��ϴ�" + std::string(_TitleName));
        return;
    }

    //�������� hdc�� ���⼭ ����
    BackBuffer = GetDC(WindowHandle);
}

void UEngineWindow::Open(std::string_view _TitleName)
{
    if (nullptr == WindowHandle)
    {
        Create(_TitleName);
    }

    if (0 == WindowHandle)
    {
        return;
    }

    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
}

void UEngineWindow::SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale)
{
    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    ::SetWindowPos(WindowHandle, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);

}



