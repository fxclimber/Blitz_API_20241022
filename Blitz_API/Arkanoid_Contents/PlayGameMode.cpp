#include "PreCompiledFile.h"
#include "playGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "Arkanoid_Contents/Ball.h"
#include "Map_Play.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	//GetWorld()->SpawnActor<Map_Play>();
	//GetWorld()->SpawnActor<ABall>();


	Map_Play* NewActor = GetWorld()->SpawnActor<Map_Play>();

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('N'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Ending");
	}

}
