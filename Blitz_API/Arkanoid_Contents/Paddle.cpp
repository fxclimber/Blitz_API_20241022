#include "PreCompiledFile.h"
#include "Paddle.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"


Paddle::Paddle()
{
	SetActorLocation({ 500,1200 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();		
		SpriteRenderer->SetOrder(ERenderOrder::Bricks);

		SpriteRenderer->CreateAnimation("paddle_materialize", "paddle_materialize", 0, 14, 0.12f);
		SpriteRenderer->ChangeAnimation("paddle_materialize");
		SpriteRenderer->SetComponentScale({ 125, 34 });
		//FVector2D PaddleScale = SpriteRenderer->SetSpriteScale(1.0f);
	}

	this;
	//{

	//// static sprite
	//USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetOrder(ERenderOrder::Bricks);
	//SpriteRenderer->SetSprite("paddle.png");
	//FVector2D PaddleScale = SpriteRenderer->SetSpriteScale(1.0f);

	//}

}

Paddle::~Paddle()
{
}

void Paddle::BeginPlay()
{
}

void Paddle::Tick(float _DeltaTime)
{
	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	//SpriteRenderer->ChangeAnimation("paddle_materialize");
	//	AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	//SpriteRenderer->ChangeAnimation("paddle_laser");
	//	AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	//SpriteRenderer->ChangeAnimation("powerup_catch");
	//	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	//}
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	//SpriteRenderer->ChangeAnimation("enemy_molecule");
	//	AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	//}


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
