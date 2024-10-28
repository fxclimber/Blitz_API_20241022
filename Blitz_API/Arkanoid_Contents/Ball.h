#pragma once
#include <EngineCore/Actor.h>

class ABall : public AActor
{
public:
	ABall();
	~ABall();

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void MoveFunction(FVector2D _Dir);

private:
	float Speed = 100.0f;


};

