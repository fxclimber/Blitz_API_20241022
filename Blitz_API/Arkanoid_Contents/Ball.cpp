#include "PreCompiledFile.h"
#include "Ball.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWinImage.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ABall::ABall()
{
	SetActorLocation({ 600,600});

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("ball_blue.png");
	SpriteRenderer->SetComponentScale({ 22, 22 });
	SpriteRenderer->SetOrder(ERenderOrder::PLAYER);

	Speed = 500.f;
}

ABall::~ABall()
{
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
}

void ABall::Tick(float _DeltaTime)
{

}


void ABall::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	AddActorLocation(_Dir * DeltaTime * Speed);
}

