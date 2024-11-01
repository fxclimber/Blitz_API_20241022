#include "PreCompiledFile.h"
#include "Map_Title.h"


#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

Map_Title::Map_Title()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("Map_Title.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}

}

Map_Title::~Map_Title()
{
}
