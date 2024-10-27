#include "PreCompiledFile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

//1�� ������ �ٲ������� ����Ÿ
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

	//�������ھ��� �����ͺ����� �ڽ� ��ü�����͸� ��ĳ�������� ����
	UserCore = _UserCore;
	//������ �ʱ�ȭ�Լ� ȣ��
	UEngineWindow::EngineWindowInit(_Inst);
	//�����ھ� ��ü ����
	UEngineAPICore Core = UEngineAPICore();
	//���� ��ü�� �����캯���� open�Լ�ȣ��
	Core.EngineMainWindow.Open();
	//UEngineWindow::Open();
	MainCore = &Core;//�����ھ���� ��ü������ ����
	// ��������Ʈ ��üStart - UEngineAPICore::EngineBeginPlay ���ε�
	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	// ��������Ʈ ��üFrameLoop - UEngineAPICore::EngineTick ���ε�
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));
	//�����ھ ������ �����Ҽ��ִ°�.. WindowMessageLoop �Լ��ȿ��� 
	// 	(int)msg.wParam;(������)�� �����ϴ°� �����ذŴ�
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}


void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}


void UEngineAPICore::EngineTick()
{
	UserCore->Tick();//�ð�,�̺�Ʈ,������,�浹
	MainCore->Tick();
}

void UEngineAPICore::Tick()
{
	//�ð����,����ð�
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();


	if (nullptr == CurLevel)
	{
		MSGASSERT("�����ھ ���緹���� ���������ʾҴ�");
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
		MSGASSERT(ChangeName + "��� �̸��� ������ ���������ʴ´�");
		return;
	}
	CurLevel = FindeIter->second;
}
