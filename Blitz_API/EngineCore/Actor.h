#pragma once
#include <EngineBase/EngineMath.h>


class AActor
{
public:
	friend class ULevel;

	AActor();
	~AActor();

	virtual void BeginPlay(){}
	virtual void Tick(float _DeltaTime){}
	virtual void Render();

	class ULevel* GetWorld()
	{
		return World;
	}

	void SetActorLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}

	void AddActorLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

	FVector2D GetActorLocation()
	{
		return Transform.Location;
	}

protected:

private:
	class ULevel* World = nullptr;

	FTransform Transform;
};

typedef AActor Super;
