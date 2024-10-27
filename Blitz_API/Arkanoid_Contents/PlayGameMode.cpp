#include "PreCompiledFile.h"
#include "playGameMode.h"
#include <EngineCore/Level.h>
#include "Arkanoid_Contents/Ball.h"
#include "Player.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	// 플레이어가 만들어져 있다면. BeginPlay();
// 감안하고 짜셔야 합니다.


// GetWorld()->SpawnActor<BackGround>();

// GetWorld()->SpawnActor<Monster>();

// 플레이어를 만들필요가 없게 되었다.
// MainPawn을 지정하는 방식으로 가기로 했으므로.
// GetWorld()->SpawnActor<Player>();


	GetWorld()->SpawnActor<ABall>();


	int a = 0;
}
