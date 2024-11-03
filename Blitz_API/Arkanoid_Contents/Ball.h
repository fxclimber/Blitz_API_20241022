#pragma once
#include <EngineCore/Actor.h>

class ABall : public AActor
{
public:
	ABall();
	~ABall();

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);

	USpriteRenderer* GetRender()
	{
		return SpriteRenderer;
	}

	FVector2D& SetVel(FVector2D _dir)
	{
		vel.X *= _dir.X;
		vel.Y *= _dir.Y;
		return vel;
	}

	const FVector2D& GetVel() const
	{
		return vel;
	}
	FVector2D vel = {0.f,0.f};

private:
	float Speed = 300.0f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

};

