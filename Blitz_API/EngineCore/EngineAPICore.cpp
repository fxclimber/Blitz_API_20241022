#include "PreCompiledFile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

//1번 세팅후 바뀌지않을 데이타
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

#include <Windows.h>

UEngineAPICore::UEngineAPICore()
{
}

UEngineAPICore::~UEngineAPICore()
{
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}
		Levels.clear();
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//컨텐츠코어의 포인터변수에 자식 객체포인터를 업캐스팅으로 대입
	UserCore = _UserCore;
	//윈도우 초기화함수 호출
	UEngineWindow::EngineWindowInit(_Inst);
	//엔진코어 객체 생성
	UEngineAPICore Core = UEngineAPICore();
	//엔진 객체의 윈도우변수의 open함수호출
	Core.EngineMainWindow.Open();
	//UEngineWindow::Open();
	MainCore = &Core;//메인코어변수에 객체포인터 대입
	// 델리게이트 객체Start - UEngineAPICore::EngineBeginPlay 바인드
	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	// 델리게이트 객체FrameLoop - UEngineAPICore::EngineTick 바인드
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));
	//엔진코어가 윈도우 리턴할수있는건.. WindowMessageLoop 함수안에서 
	// 	(int)msg.wParam;(정수형)을 리턴하는걸 맞춰준거다
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}


void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}


void UEngineAPICore::EngineTick()
{
	UserCore->Tick();//시간,이벤트,렌더링,충돌
	MainCore->Tick();
}

void UEngineAPICore::Tick()
{
	//시간재기,현재시간
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();


	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진코어에 현재레벨이 지정되지않았다");
		return;
	}
	CurLevel->Tick(DeltaTime);
	CurLevel->Render();
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	std::map<std::string, class ULevel*>::iterator FindeIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindeIter)
	{
		MSGASSERT(ChangeName + "라는 이름의 레벨은 존재하지않는다");
		return;
	}
	CurLevel = FindeIter->second;
}
