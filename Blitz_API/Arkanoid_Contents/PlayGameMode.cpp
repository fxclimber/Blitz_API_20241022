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
	// �÷��̾ ������� �ִٸ�. BeginPlay();
// �����ϰ� ¥�ž� �մϴ�.


// GetWorld()->SpawnActor<BackGround>();

// GetWorld()->SpawnActor<Monster>();

// �÷��̾ �����ʿ䰡 ���� �Ǿ���.
// MainPawn�� �����ϴ� ������� ����� �����Ƿ�.
// GetWorld()->SpawnActor<Player>();


	GetWorld()->SpawnActor<ABall>();


	int a = 0;
}
