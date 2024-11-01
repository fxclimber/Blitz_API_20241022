#include "PreCompiledFile.h"
#include "EndGameMode.h"
#include "Map_Ending.h"


AEndGameMode::AEndGameMode()
{
}

AEndGameMode::~AEndGameMode()
{
}

void AEndGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);
	Map_Ending* NewActor = GetWorld()->SpawnActor<Map_Ending>();


}
