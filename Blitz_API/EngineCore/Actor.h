#pragma once
#include <EngineBase/EngineMath.h>

class AActor
{
public:
	friend class ULevel;

	AActor();
	~AActor();

	virtual void BeginPlay(){}
	virtual void Tick(){}
	virtual void Render();

	class ULevel* GetWorld()
	{
		return World;
	}

	void SetActorLocation(FVector2D _Location)
	{
		Location = _Location;
	}

	void AddActorLocation(FVector2D _Direction)
	{
		Location += _Direction;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Scale = _Scale;
	}


private:
	class ULevel* World = nullptr;

	FVector2D Location = FVector2D::ZERO;
	FVector2D Scale = FVector2D::ZERO;

};

