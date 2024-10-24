#include "PreCompiledFile.h"
#include "Actor.h"
#include <EngineCore/EngineAPICore.h>

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render()
{
	FVector2D LeftTop = Location - Scale.Half();
	FVector2D RoghtTop = Location + Scale.Half();


}
