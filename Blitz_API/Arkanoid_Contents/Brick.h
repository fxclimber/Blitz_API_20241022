#pragma once
#include <EngineCore/Actor.h>


class Brick : public AActor
{

public:
	Brick();
	~Brick();

	void BeginPlay()override;
	void Tick(float _DeltaTime) override;
	USpriteRenderer* GetRender()
	{
		return SpriteRenderer;
	}
	FVector2D CheckCollision(const FVector2D& playerPos, const FVector2D& playerSize);

protected:

private:
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

};

