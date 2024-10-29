#include "PreCompiledFile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include "Ball.h"
#include <iostream>
#include <EnginePlatform/EngineWinImage.h>
#include "Bullet.h"


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



void APlayMap::PrintWhereIsBall(FVector2D _Dir)
{
    FVector2D Pos = ABall::Pos;
    ABullet* SpawnBullet = GetWorld()->SpawnActor<ABullet>();
    SpawnBullet->SetActorLocation(Pos);
    SpawnBullet->MoveFunction(_Dir);
}




void APlayMap::Tick(float _DeltaTime)
{
    FVector2D BallPos = ABall::Pos;

    FVector2D Location = { 450, 450 }; // �簢���� ���� �� ������
    FVector2D Scale = { 300, 150 }; // �簢���� ũ�� (�ʺ�, ����)
    FVector2D Center = { Location.X + Scale.X / 2, Location.Y + Scale.Y / 2 };

    // �� �𼭸� ��ǥ
    FVector2D TopLeft = Location;
    FVector2D TopRight = { Location.X + Scale.X, Location.Y };
    FVector2D BottomLeft = { Location.X, Location.Y + Scale.Y };
    FVector2D BottomRight = { Location.X + Scale.X, Location.Y + Scale.Y };

    // ��ġ �Ǻ� �Լ�
    auto DetermineTriangle = [&](const FVector2D& P) -> WhereIsBall
        {
            if (P.Y < Center.Y && P.X >= TopLeft.X && P.X <= TopRight.X)
            {
                return WhereIsBall::UP;
            }
            else if (P.Y > Center.Y && P.X >= BottomLeft.X && P.X <= BottomRight.X)
            {
                return WhereIsBall::DOWN;
            }
            else if (P.X < Center.X && P.Y >= TopLeft.Y && P.Y <= BottomLeft.Y)
            {
                return WhereIsBall::LEFT;
            }
            else if (P.X > Center.X && P.Y >= TopRight.Y && P.Y <= BottomRight.Y)
            {
                return WhereIsBall::RIGHT;
            }
            else
            {
                return WhereIsBall::NONE;
            }
        };

    // ���� ���� �ﰢ�� ��ġ �Ǻ�
    WhereIsBall position = DetermineTriangle(BallPos);

    // ���� �α� - �׽�Ʈ ����ġ ���
    UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
    UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
    HDC dc = WindowImage->GetDC();  // HDC�� ������

    // ȭ���� ����� ���� �۾� �߰� (���⼭ ��� ���� ����� �Լ� �ʿ�)
    // ��: FillRect(dc, &rect, (HBRUSH)(COLOR_WINDOW + 1));  // rect�� ��ü ȭ�� ����

    std::wstring str = L"Pos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
    TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));

    // �ﰢ�� ��ġ�� ���� ���� ����
    switch (position) {
    case WhereIsBall::UP:
        TextOutW(dc, 600, 600, L"Ball Position UP", 20);
        break;
    case WhereIsBall::DOWN:
        TextOutW(dc, 600, 600, L"Ball Position DOWN", 20);
        break;
    case WhereIsBall::LEFT:
        TextOutW(dc, 600, 600, L"Ball Position LEFT", 20);
        break;
    case WhereIsBall::RIGHT:
        TextOutW(dc, 600, 600, L"Ball Position RIGHT", 20);
        break;
    case WhereIsBall::NONE:
    default:
        TextOutW(dc, 600, 600, str.c_str(), static_cast<int>(str.size()));
        break;
    }

   // WindowImage->ReleaseDC(dc);  // HDC�� ����//�츮���� ReleaseDC����
}
