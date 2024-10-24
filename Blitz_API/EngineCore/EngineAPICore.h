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
	//다형성 사용을 위해 순수가상함수사용
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

//언리얼의  GEngine
class UEngineAPICore
{
public:
	UEngineAPICore();
	~UEngineAPICore();

	//게임을 시작시킬 함수
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
		//게임모드가 레벨특성을 설정하는 중요객체이므로
		NewLevel->CreateGameMode<GameModeType, MainPawnType>();
		//관리, 삭제객체만들고,객체안에 자료구조 넣고,자료구조안에 새로운 객체들을 보관
		Levels.insert({_LevelName.data(), NewLevel});

		return NewLevel;
	}

	void OpenLevel(std::string_view _LevelName);


protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;//자신을 포인터전역으로 갖고있다
	static UContentsCore* UserCore;

	UEngineWindow EngineMainWindow; //엔진 메인 윈도우

	//만들어진 모든 레벨
	std::map<std::string, class ULevel*> Levels;
	//현재 내가 보는 레벨,포인터 체인지 방식
	class ULevel* CurLevel = nullptr;

	//게임실행동안 계속 돌 함수
	void Tick();


};

