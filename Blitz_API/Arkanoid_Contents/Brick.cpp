#include "PreCompiledFile.h"
#include "Brick.h"


#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"


Brick::Brick()
{


	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::Bricks);
		SpriteRenderer->SetSprite("brick_blue.png");

		FVector2D BrickScale = SpriteRenderer->SetSpriteScale(5.0f);
		SpriteRenderer->SetComponentLocation(BrickScale.Half());
		//SpriteRenderer->SetComponentLocation({ 0,0 });
		SetActorLocation({0,0});
		//FTransform ft = this->GetTransform();
		//ft.CenterLeftTop();
	}

}

Brick::~Brick()
{
}

void Brick::BeginPlay()
{
}

void Brick::Tick(float _DeltaTime)
{
}


