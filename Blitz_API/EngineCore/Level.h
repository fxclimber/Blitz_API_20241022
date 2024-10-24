#pragma once
#include "GameMode.h"

class ULevel
{
public:
	friend class UEngineAPICore;

	ULevel();
	~ULevel();

	void Tick();
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
	//���ӷ���,�������� ����� ������ �غ��Ű�� �Լ��� ����
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();
		//���弼���� �����Ǵ°��� �߿���
		MainPawn->World = this;
		GameMode->World = this;

		MainPawn->BeginPlay();
		GameMode->BeginPlay();

		AllActors.push_back(GameMode);
		AllActors.push_back(MainPawn);
	}

	AGameMode* GameMode = nullptr;
	//���ΰ�
	AActor* MainPawn = nullptr;
	std::list<AActor*> AllActors;
};

