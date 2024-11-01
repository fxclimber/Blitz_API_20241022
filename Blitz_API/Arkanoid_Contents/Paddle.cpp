#include "PreCompiledFile.h"
#include "Paddle.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>


Paddle::Paddle()
{
	SetActorLocation({ 100, 100 });
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();		
		SpriteRenderer->SetComponentScale({ 200, 40 });
		SpriteRenderer->CreateAnimation("paddle_materialize", "paddle_materialize", 0, 14, 0.15f);
		SpriteRenderer->ChangeAnimation("paddle_materialize");
	}

	this;
	SetActorLocation({ 400,400 });

	//SpriteRenderer->CreateAnimation("paddle_laser" , 0, 15, 0.7f);
	//SpriteRenderer->CreateAnimation("powerup_catch" , 0, 7, 0.3f);
	//SpriteRenderer->CreateAnimation("enemy_molecule" , 0, 24, 1.0f);

}

Paddle::~Paddle()
{
}

void Paddle::BeginPlay()
{
}

void Paddle::Tick(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		//SpriteRenderer->ChangeAnimation("paddle_materialize");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		//SpriteRenderer->ChangeAnimation("paddle_laser");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		//SpriteRenderer->ChangeAnimation("powerup_catch");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		//SpriteRenderer->ChangeAnimation("enemy_molecule");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	//if (false == UEngineInput::GetInst().IsPress('A') &&
	//	false == UEngineInput::GetInst().IsPress('D') &&
	//	false == UEngineInput::GetInst().IsPress('W') &&
	//	false == UEngineInput::GetInst().IsPress('S'))
	{
		//SpriteRenderer->ChangeAnimation("paddle_materialize");
	}

}

void Paddle::MoveFunction(FVector2D _Dir)
{
}

void Paddle::RunSoundPlay()
{
}

void Paddle::LevelChangeStart()
{
}

void Paddle::LevelChangeEnd()
{
}
