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
	SetActorScale({ 40,40 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("ball_blue.png");
	SpriteRenderer->SetComponentScale({ 22, 22 });
	SpriteRenderer->SetOrder(ERenderOrder::PLAYER);

	//SpriteRenderer->Render()
	Speed = 500.f;

}

ABall::~ABall()
{
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	//UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::LEFT));
	//UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::RIGHT));
	//UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::DOWN));
	//UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::UP));

}

void ABall::Tick(float _DeltaTime)
{

}



void ABall::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	AddActorLocation(_Dir * DeltaTime * Speed);
}

