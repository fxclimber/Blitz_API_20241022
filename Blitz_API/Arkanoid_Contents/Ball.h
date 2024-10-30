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

	//void Render()override;
	static FVector2D Pos;
private:
	float Speed = 100.0f;
	FVector2D Location = FVector2D::ZERO;
	FVector2D Scale = FVector2D::ZERO;
	int MySpriteIndex = 0;


};

