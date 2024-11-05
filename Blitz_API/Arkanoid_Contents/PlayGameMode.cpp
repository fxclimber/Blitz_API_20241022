#include "PreCompiledFile.h"
#include "playGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include "TileMapGameMode.h"
#include <EngineCore/Level.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include "Arkanoid_Contents/Ball.h"
#include "Map_Play.h"
#include "Player.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"

#include <string>

//void LogToOutputWindow(const std::string& message) {
//	OutputDebugString(message.c_str());
//}

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

	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
	}

	{
		WallTileMap = GetWorld()->SpawnActor<ATileMap>();
		WallTileMap->Create("Brick", { 10, 12 }, { 77, 38 });

		for (int y = 0; y < 12; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				WallTileMap->SetTileIndex({ y,x }, { 0, 0 }, { 77, 38 }, 0);
			}
		}

	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Data");
		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("rb");
		UEngineSerializer Ser;
		NewFile.Read(Ser);
		WallTileMap->DeSerialize(Ser);

	}


	Map_Play* NewActor = GetWorld()->SpawnActor<Map_Play>();
	//APlayer* Player = GetWorld()->SpawnActor<APlayer>();
	Player = GetWorld()->SpawnActor<APlayer>();
	paddle = GetWorld()->SpawnActor<Paddle>();
	brick = GetWorld()->SpawnActor<Brick>();
	ball = GetWorld()->SpawnActor<ABall>();
	ball->SetActorLocation((paddle->GetActorLocation()) + ball->GetRender()->GetComponentScale()/2);
	FVector2D ballInitVel = { 0.7f,-1.f };
	ball->vel = ballInitVel;
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int MaxTop = 122;
	int MaxBottom = 1250;
	int MaxLeft = 52;
	int MaxRight = 948;

	FVector2D ballPos = ball->GetActorLocation();
	FVector2D ballScale = ball->GetRender()->GetComponentScale();
	float tolerance = 0.02f + ballScale.X / 2;
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	// 공이 벽 내부에서만 이동하도록 설정
	if (MaxLeft < ballPos.X && ballPos.X < MaxRight && MaxTop < ballPos.Y && ballPos.Y < MaxBottom)
	{
		// 왼쪽 및 오른쪽 벽에 닿았는지 확인
		if (ballPos.X <= MaxLeft + tolerance || ballPos.X >= MaxRight - tolerance)
		{
			ball->vel.X *= -1.0f; // X축 반전
		}

		// 위쪽 및 아래쪽 벽에 닿았는지 확인
		if (ballPos.Y <= MaxTop + tolerance || ballPos.Y >= MaxBottom - tolerance)
		{
			ball->vel.Y *= -1.0f; // Y축 반전
		}
	}

	// 반사 속도로 공 이동
	ball->MoveFunction(ball->vel);

	UEngineDebug::CoreOutPutString("ballVel : " + ball->vel.ToString(), { 100,200 });






	// 디버그 출력 
	FVector2D playerPos = Player->GetTransform().Location;
	FVector2D brickPos = brick->GetTransform().Location;
	FVector2D brickSpriteScale = brick->GetRender()->GetComponentScale();

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + playerPos.ToString(), playerPos+ FVector2D(25, -80));
	UEngineDebug::CoreOutPutString("brickPos : " + brickPos.ToString(), { 100,130 });


	// 맵이동 키입력
	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Ending");
	}

	// 벽돌파츠 판정
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

			UEngineDebug::CoreOutPutString("vel : " + reflected.ToString(), FVector2D(100, 640));



}





// 반사 벡터 계산 함수
FVector2D APlayGameMode::Reflect(const FVector2D& incoming, const FVector2D& normal)
{
	// 입사 벡터와 법선 벡터의 도트 곱
	float dotProduct = incoming.Dot(normal);
	return incoming - normal * (2 * dotProduct);
}

FVector2D APlayGameMode::GetVectorForBallPos(WhereIsBall position)
{
	switch (position) {
	case WhereIsBall::TOP:
		return FVector2D(0.0f, 1.0f); // 위쪽
	case WhereIsBall::BOTTOM:
		return FVector2D(0.0f, -1.0f); // 아래쪽
	case WhereIsBall::LEFT:
		return FVector2D(-1.0f, 0.0f); // 왼쪽
	case WhereIsBall::RIGHT:
		return FVector2D(1.0f, 0.0f); // 오른쪽
	default:
		return FVector2D(0.0f, 0.0f); // NONE 또는 예외처리
	}
}