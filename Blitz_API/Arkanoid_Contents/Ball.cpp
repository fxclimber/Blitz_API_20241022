#include "PreCompiledFile.h"
#include "Ball.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWinImage.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>


FVector2D ABall::Pos;


ABall::ABall()
{
	SetActorLocation({ 600,600});
	SetActorScale({ 40,40 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("characters.png");
	SpriteRenderer->SetComponentScale({ 100, 100 });


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



void ABall::MoveFunction(FVector2D _Dir)
{

	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);

}


void ABall::Tick(float _DeltaTime)
{
	GetActorLocation();

	this;




		if (true == UEngineInput::GetInst().IsPress('D'))
	{
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

	Pos = GetActorLocation();
}