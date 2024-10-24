#pragma once
#include <string>

#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

class UContentsCore
{
public:
	//������ ����� ���� ���������Լ����
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

//�𸮾���  GEngine
class UEngineAPICore
{
public:
	UEngineAPICore();
	~UEngineAPICore();

	//������ ���۽�ų �Լ�
	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);

	static class UEngineAPICore* GetCore()
	{
		return MainCore;
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		ULevel* NewLevel = new ULevel();
		//���Ӹ�尡 ����Ư���� �����ϴ� �߿䰴ü�̹Ƿ�
		NewLevel->CreateGameMode<GameModeType, MainPawnType>();
		//����, ������ü�����,��ü�ȿ� �ڷᱸ�� �ְ�,�ڷᱸ���ȿ� ���ο� ��ü���� ����
		Levels.insert({_LevelName.data(), NewLevel});

		return NewLevel;
	}

	void OpenLevel(std::string_view _LevelName);


protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;//�ڽ��� �������������� �����ִ�
	static UContentsCore* UserCore;

	UEngineWindow EngineMainWindow; //���� ���� ������

	//������� ��� ����
	std::map<std::string, class ULevel*> Levels;
	//���� ���� ���� ����,������ ü���� ���
	class ULevel* CurLevel = nullptr;

	//���ӽ��ൿ�� ��� �� �Լ�
	void Tick();


};

