#include "PreCompiledFile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include "Ball.h"
#include <iostream>
#include <EnginePlatform/EngineWinImage.h>

APlayMap::APlayMap()
{
	//FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	//SetActorScale(WindowSize.Half());
	//SetActorLocation(WindowSize.Half());

	SetActorLocation({ 450,450 });
	SetActorScale({ 300, 150 });


}

APlayMap::~APlayMap()
{
}

void APlayMap::Tick(float _DeltaTime)
{
	FVector2D BallPos = ABall::Pos;

    FVector2D Location = { 450, 450 };      // 사각형의 왼쪽 위 꼭짓점
    FVector2D Scale = { 300, 150 };         // 사각형의 크기 (너비, 높이)
    FVector2D P = BallPos;                  // 검사할 점 위치

    // 사각형의 중심점 계산
    FVector2D Center = { Location.X + Scale.X / 2, Location.Y + Scale.Y / 2 };

    // 각 모서리 좌표
    FVector2D TopLeft = Location;
    FVector2D TopRight = { Location.X + Scale.X, Location.Y };
    FVector2D BottomLeft = { Location.X, Location.Y + Scale.Y };
    FVector2D BottomRight = { Location.X + Scale.X, Location.Y + Scale.Y };

    if (P.Y < Center.Y && P.X >= TopLeft.X && P.X <= TopRight.X)
    {
        WhereIsBall::UP;
    }
    // 하단 삼각형 (BottomLeft - Center - BottomRight)
    else if (P.Y > Center.Y && P.X >= BottomLeft.X && P.X <= BottomRight.X) 
    {
        WhereIsBall::DOWN;
    }
    // 좌측 삼각형 (TopLeft - Center - BottomLeft)
    else if (P.X < Center.X && P.Y >= TopLeft.Y && P.Y <= BottomLeft.Y) 
    {
        WhereIsBall::LEFT;
    }
    // 우측 삼각형 (TopRight - Center - BottomRight)
    else if (P.X > Center.X && P.Y >= TopRight.Y && P.Y <= BottomRight.Y) 
    {
        WhereIsBall::RIGHT;
    }
    else 
    {
        WhereIsBall::NONE;
    }
}

