#pragma once
#include <EngineCore/GameMode.h>
#include "ATileMap.h"


enum class WhereIsBall
{
	NONE,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
};

class APlayGameMode : public AGameMode
{
public:
	APlayGameMode();
	~APlayGameMode();
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	FVector2D Reflect(const FVector2D& incoming, const FVector2D& normal);
	FVector2D reflected = { 0,0 };

	WhereIsBall ballEnum;
	FVector2D GetVectorForBallPos(WhereIsBall position);

protected:

private:
	class APlayer* Player = nullptr;
	class Paddle* paddle = nullptr;
	class Brick* brick = nullptr;
	class ABall* ball = nullptr;

	ATileMap* WallTileMap = nullptr;
	ATileMap* GroundTileMap = nullptr;

	std::string LoadFileName;

};

