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

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
	MSG msg = MSG();//윈도우에 반응?이 있으면 메세지 생성

    if (true == _StartFunction.IsBind())
    {
        _StartFunction();//델리게이트 함수리스트에 연결있으면(있다.시작,루프2개) 함수호출
    }

	while (0 != WindowCount)//윈도우있으면,있지? 코어에서 멤버로 만들었으니,
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
    //키보드,마우스의 입력을 정수로 캐스팅(int)해서, 프로그램종료를 호출자에게 알림. 
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
}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    // 클래스이름이 중요하다.
    // _ClassName이 데이타에 contains아니면,
    if (false == WindowClass.contains(_ClassName.data()))
    {
        MSGASSERT("등록하지않은 클래스로 윈도우창을 만들려고 했습니다" + std::string(_ClassName));
        return;
    }

    //WindowHandle = CreateWindowA(_ClassName.data(),_TitleName.data(), WS_OVERLAPPEDWINDOW,
    //    0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    // HWND 윈도우핸들을 리턴.
    WindowHandle = CreateWindowA(
        _ClassName.data(),   // 윈도우 클래스 이름 (등록된 클래스명)
        _TitleName.data(),   // 윈도우 제목
        WS_OVERLAPPEDWINDOW, // 윈도우 스타일 (타이틀바, 최대화, 최소화 버튼 포함)
        0,                   // 윈도우의 초기 x 위치
        0,                   // 윈도우의 초기 y 위치
        CW_USEDEFAULT,       // 기본 너비를 지정
        0,                   // 기본 높이를 지정 (CW_USEDEFAULT로 지정 가능)
        nullptr,             // 부모 윈도우 핸들 (없다면 nullptr)
        nullptr,             // 메뉴 핸들 (없다면 nullptr)
        hInstance,           // 현재 애플리케이션 인스턴스 핸들
        nullptr              // 추가 매개변수 (필요 없으면 nullptr)
    );


    if ( nullptr == WindowHandle)
    {
        MSGASSERT("윈도우 생성에 실패했습니다" + std::string(_TitleName));
        return;
    }

    //윈도우의 hdc를 여기서 얻음
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



