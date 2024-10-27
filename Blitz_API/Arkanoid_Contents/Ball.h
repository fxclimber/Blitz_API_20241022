#pragma once
#include <EngineCore/Actor.h>

class ABall : public AActor
{
public:
	ABall();
	~ABall();

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Render() override;



	class ULevel* GetWorld()
	{
		return World;
	}

	FVector2D GetActorLocation()
	{
		return Location;
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
	float Speed = 100.0f;


};

