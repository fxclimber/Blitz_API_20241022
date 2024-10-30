#pragma once
#include <EngineCore/Actor.h>

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);

protected:

private:
	float Speed = 100.0f;
	int MySpriteIndex = 0;

};

