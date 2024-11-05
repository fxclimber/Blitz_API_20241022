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

protected:

private:
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

};

