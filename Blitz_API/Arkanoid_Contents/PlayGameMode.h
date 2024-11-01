#pragma once
#include <EngineCore/GameMode.h>

class APlayGameMode : public AGameMode
{
public:
	APlayGameMode();
	~APlayGameMode();
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	class APlayer* Player = nullptr;
	class Paddle* paddle = nullptr;
	class Brick* brick = nullptr;
};

