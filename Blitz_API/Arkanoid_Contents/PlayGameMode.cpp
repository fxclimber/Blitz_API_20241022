#include "PreCompiledFile.h"
#include "playGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>


#include "Arkanoid_Contents/Ball.h"
#include "Map_Play.h"
#include "Player.h"
#include "Paddle.h"
#include "Brick.h"


#include <string>

void LogToOutputWindow(const std::string& message) {
	OutputDebugString(message.c_str());
}

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SetCameraToMainPawn(false);

	Map_Play* NewActor = GetWorld()->SpawnActor<Map_Play>();
	//APlayer* Player = GetWorld()->SpawnActor<APlayer>();
	Player = GetWorld()->SpawnActor<APlayer>();
	paddle = GetWorld()->SpawnActor<Paddle>();
	brick = GetWorld()->SpawnActor<Brick>();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// ����� ��� ����
	FVector2D playerPos = Player->GetTransform().Location;
	FVector2D brickPos = brick->GetTransform().Location;
	//FVector2D brickScale = brick->GetTransform().Scale;
	//USpriteRenderer* SpriteRenderer = brick->GetRender();
	FVector2D brickSpriteScale = brick->GetRender()->GetComponentScale();
	//FVector2D WinSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + playerPos.ToString(), playerPos+ FVector2D(25, -80));
	//UEngineDebug::CoreOutPutString("WinSize : " + WinSize.ToString(), { 100,100 });
	UEngineDebug::CoreOutPutString("brickPos : " + brickPos.ToString(), { 100,130 });
	//UEngineDebug::CoreOutPutString("brickSpriteScale : " + brickSpriteScale.ToString(), { 100,155 });


	// ���̵� Ű�Է�
	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Ending");
	}

	// �������� ����
	{
		FVector2D HitResult = (playerPos-brickPos) / brickSpriteScale;
		if (HitResult.X > 0 && HitResult.Y > 0 && HitResult.X < 1 && HitResult.Y < 1)
		{
			if(HitResult.X<HitResult.Y)//left,bottom
			{
				if (HitResult.X > 1- HitResult.Y)
				{
				UEngineDebug::CoreOutPutString("HitResult : BOTTOM" + HitResult.ToString(),FVector2D(100, 600));
				ballEnum = WhereIsBall::BOTTOM;
				}
				else
				{
				UEngineDebug::CoreOutPutString("HitResult : LEFT" + HitResult.ToString(), FVector2D(100, 600));
				ballEnum = WhereIsBall::LEFT;
				}
			}
			else if (HitResult.X > HitResult.Y)//right, top
			{
				if (HitResult.Y > 1 - HitResult.X)
				{
					UEngineDebug::CoreOutPutString("HitResult : RIGHT" + HitResult.ToString(), FVector2D(100, 600));
					ballEnum = WhereIsBall::RIGHT;
				}
				else
				{
					UEngineDebug::CoreOutPutString("HitResult : TOP" + HitResult.ToString(), FVector2D(100, 600));
					ballEnum = WhereIsBall::TOP;
				}
				
			}
			else
			{
				UEngineDebug::CoreOutPutString("HitResult : " + HitResult.ToString(), FVector2D(100, 600));
			}
		}
		else
		{
		UEngineDebug::CoreOutPutString("HitResult : " + HitResult.ToString(), FVector2D(100, 600));
		}

	}

	//FVector2D incoming(1.0f,-1.0f);
	FVector2D incoming = GetVectorForBallPos(ballEnum);
	FVector2D normal(0.0f, 1.0f);
	reflected = Reflect(incoming, normal);
	UEngineDebug::CoreOutPutString("reflected : " + reflected.ToString(), FVector2D(100, 640));


	//MoveFunction
		if (true == UEngineInput::GetInst().IsPress('X'))
		{
			if (false == Player->IsMoving())
			{
			Player->MoveFunction(reflected);
			}
		}




}





// �ݻ� ���� ��� �Լ�
FVector2D APlayGameMode::Reflect(const FVector2D& incoming, const FVector2D& normal)
{
	// �Ի� ���Ϳ� ���� ������ ��Ʈ ��
	float dotProduct = incoming.dot(normal);
	return incoming - normal * (2 * dotProduct);
}

FVector2D APlayGameMode::GetVectorForBallPos(WhereIsBall position)
{
	switch (position) {
	case WhereIsBall::TOP:
		return FVector2D(0.0f, 1.0f); // ����
	case WhereIsBall::BOTTOM:
		return FVector2D(0.0f, -1.0f); // �Ʒ���
	case WhereIsBall::LEFT:
		return FVector2D(-1.0f, 0.0f); // ����
	case WhereIsBall::RIGHT:
		return FVector2D(1.0f, 0.0f); // ������
	default:
		return FVector2D(0.0f, 0.0f); // NONE �Ǵ� ����ó��
	}
}