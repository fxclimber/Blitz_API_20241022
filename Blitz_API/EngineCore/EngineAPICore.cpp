#include "PreCompiledFile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

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
		Levels.clear();
	}
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));
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
	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진코어에 현재레벨이 지정되지않았다");
		return;
	}
	CurLevel->Tick();
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
