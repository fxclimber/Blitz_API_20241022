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

	GetWorld()->SpawnActor<ABall>();

}
