#pragma once
#include "GameMode.h"

class ULevel
{
public:
	friend class UEngineAPICore;

	ULevel();
	~ULevel();

	void Tick(float _DeltaTime);
	void Render();

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();
		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;

		NewActor->BeginPlay();
		AllActors.push_back(NewActor);
		return NewActor;
	}

protected:

private:
	void ScreenClear();
	void DoubleBuffering();

	//게임레벨,메인폰을 만들어 게임을 준비시키는 함수로 만듬
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		//화면을 보는 카메라
		MainPawn = new MainPawnType();
		//월드세팅이 먼저되는것이 중요
		MainPawn->World = this;
		GameMode->World = this;

		MainPawn->BeginPlay();
		GameMode->BeginPlay();

		AllActors.push_back(GameMode);
		AllActors.push_back(MainPawn);
	}

	AGameMode* GameMode = nullptr;
	//주인공
	AActor* MainPawn = nullptr;
	std::list<AActor*> AllActors;
};

