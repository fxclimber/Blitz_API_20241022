#include "PreCompiledFile.h"
#include "playGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>


#include "Arkanoid_Contents/Ball.h"
#include "Map_Play.h"
#include "Player.h"
#include "Paddle.h"
#include "Brick.h"

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
	//APlayer* Player = GetWorld()->SpawnActor<APlayer>();
	Player = GetWorld()->SpawnActor<APlayer>();
	paddle = GetWorld()->SpawnActor<Paddle>();
	brick = GetWorld()->SpawnActor<Brick>();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 디버그 출력 연습
	FVector2D playerPos = Player->GetTransform().Location;
	FVector2D brickPos = brick->GetTransform().Location;
	//FVector2D brickScale = brick->GetTransform().Scale;
	FVector2D brickSpriteScale = brick->GetRender()->GetComponentScale();
	//FVector2D WinSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + playerPos.ToString(), playerPos+ FVector2D(25, -80));
	//UEngineDebug::CoreOutPutString("WinSize : " + WinSize.ToString(), { 100,100 });
	UEngineDebug::CoreOutPutString("brickPos : " + brickPos.ToString(), { 100,130 });
	UEngineDebug::CoreOutPutString("brickSpriteScale : " + brickSpriteScale.ToString(), { 100,155 });


	// 맵이동 키입력
	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Ending");
	}

	// 벽돌파츠 판정
	//{
		FVector2D HitResult = (playerPos-brickPos) / brickSpriteScale;

	//	//if (HitResult.X > 0 && HitResult.X < 0.75 && HitResult.Y >0 && HitResult.Y < 0.75)
	//	if (HitResult.X > 0 && HitResult.X < 0.75 && HitResult.Y >0 && HitResult.Y < 0.75)
	//	{
	//		UEngineDebug::CoreOutPutString("HitResult : LEFT");
	//	}
	//	else
	//	{
	//		UEngineDebug::CoreOutPutString("HitResult : " + HitResult.ToString(), playerPos + FVector2D(25, -120));
	//	}

	//}

	UEngineDebug::CoreOutPutString("HitResult : " + HitResult.ToString(), playerPos + FVector2D(25, -120));




}
