#pragma once
#include <EngineCore/Actor.h>

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	float Speed = 100.0f;

};

