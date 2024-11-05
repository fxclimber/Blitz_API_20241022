#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineSerializer.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"

class Brick : public AActor ,public ISerializObject
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
// Ÿ���ϳ��ϳ��� �������� ũ�⸦ ������ �ִٸ�
// �̰ɷ� ���� �Է����ּž� �մϴ�.
	FVector2D Scale;
	FVector2D Pivot;
	int SpriteIndex;

	bool IsMove = true;
	int TileType = -1;

	class USpriteRenderer* SpriteRenderer;

	// �����͸� ����ȭ(����)
	void Serialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}
	void DeSerialize(UEngineSerializer& _Ser)
	{
		//std::string SpriteName;
		// _Ser >> SpriteName;

		// SpriteRenderer->SetSprite(SpriteName);

		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;

	}

protected:

private:
	int MySpriteIndex = 0;


};

