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

    FVector2D Location = { 450, 450 };      // �簢���� ���� �� ������
    FVector2D Scale = { 300, 150 };         // �簢���� ũ�� (�ʺ�, ����)
    FVector2D P = BallPos;                  // �˻��� �� ��ġ

    // �簢���� �߽��� ���
    FVector2D Center = { Location.X + Scale.X / 2, Location.Y + Scale.Y / 2 };

    // �� �𼭸� ��ǥ
    FVector2D TopLeft = Location;
    FVector2D TopRight = { Location.X + Scale.X, Location.Y };
    FVector2D BottomLeft = { Location.X, Location.Y + Scale.Y };
    FVector2D BottomRight = { Location.X + Scale.X, Location.Y + Scale.Y };

    if (P.Y < Center.Y && P.X >= TopLeft.X && P.X <= TopRight.X)
    {
        WhereIsBall::UP;
    }
    // �ϴ� �ﰢ�� (BottomLeft - Center - BottomRight)
    else if (P.Y > Center.Y && P.X >= BottomLeft.X && P.X <= BottomRight.X) 
    {
        WhereIsBall::DOWN;
    }
    // ���� �ﰢ�� (TopLeft - Center - BottomLeft)
    else if (P.X < Center.X && P.Y >= TopLeft.Y && P.Y <= BottomLeft.Y) 
    {
        WhereIsBall::LEFT;
    }
    // ���� �ﰢ�� (TopRight - Center - BottomRight)
    else if (P.X > Center.X && P.Y >= TopRight.Y && P.Y <= BottomRight.Y) 
    {
        WhereIsBall::RIGHT;
    }
    else 
    {
        WhereIsBall::NONE;
    }
}

