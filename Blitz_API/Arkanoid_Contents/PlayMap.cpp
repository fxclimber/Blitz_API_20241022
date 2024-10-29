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




//void APlayMap::Tick(float _DeltaTime)
//{
//    FVector2D BallPos = ABall::Pos;
//
//    FVector2D Location = { 450, 450 }; // �簢���� ���� �� ������
//    FVector2D Scale = { 300, 150 }; // �簢���� ũ�� (�ʺ�, ����)
//    FVector2D Center = { Location.X + Scale.X / 2, Location.Y + Scale.Y / 2 };
//
//    // �� �𼭸� ��ǥ
//    FVector2D TopLeft = Location;
//    FVector2D TopRight = { Location.X + Scale.X, Location.Y };
//    FVector2D BottomLeft = { Location.X, Location.Y + Scale.Y };
//    FVector2D BottomRight = { Location.X + Scale.X/2, Location.Y + Scale.Y };
//
//    // ��ġ �Ǻ� �Լ�
//    auto DetermineTriangle = [&](const FVector2D& P) -> WhereIsBall
//        {
//            if (P.Y < Center.Y && P.Y >TopLeft.Y && P.X >= TopLeft.X && P.X < BottomRight.X)
//            {
//                return WhereIsBall::UP;
//            }
//            else if (P.Y > Center.Y && P.Y < Location.Y+Scale.Y/2 && P.X > Location.X && P.X < (Location.X + Scale.X))
//            {
//                return WhereIsBall::DOWN;
//            }
//            //else if (P.X < Center.X && P.X > Location.X && P.Y > Location.Y && P.Y < Location.Y+Scale.Y)
//            else if (P.X < Center.X  && P.Y > Location.Y && P.Y < Location.Y+Scale.Y)
//            {
//                return WhereIsBall::LEFT;
//            }
//            //else if (P.X > Center.X && P.X < (Location.X+Scale.X) && P.Y > Location.Y && P.Y < Location.Y + Scale.Y)
//            else if (P.X > Center.X && P.X < Location.X && P.Y > Location.Y && P.Y < Location.Y + Scale.Y)
//            {
//                return WhereIsBall::RIGHT;
//            }
//            else
//            {
//                return WhereIsBall::NONE;
//            }
//        };
//
//    // ���� ���� �ﰢ�� ��ġ �Ǻ�
//    WhereIsBall position = DetermineTriangle(BallPos);
//
//    // ���� �α� - �׽�Ʈ ����ġ ���
//    UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
//    UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
//    HDC dc = WindowImage->GetDC();  // HDC�� ������
//
//    // ȭ���� ����� ���� �۾� �߰� (���⼭ ��� ���� ����� �Լ� �ʿ�)
//    // ��: FillRect(dc, &rect, (HBRUSH)(COLOR_WINDOW + 1));  // rect�� ��ü ȭ�� ����
//
//    std::wstring str = L"Pos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
//    TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));
//
//    // �ﰢ�� ��ġ�� ���� ���� ����
//    switch (position) {
//    case WhereIsBall::UP:
//        TextOutW(dc, 600, 600, L"Ball Position UP", 20);
//        //PrintWhereIsBall(FVector2D::UP);
//        break;
//    case WhereIsBall::DOWN:
//       TextOutW(dc, 600, 600, L"Ball Position DOWN", 20);
//        //PrintWhereIsBall(FVector2D::DOWN);
//        break;
//    case WhereIsBall::LEFT:
//        TextOutW(dc, 600, 600, L"Ball Position LEFT", 20);
//        //PrintWhereIsBall(FVector2D::LEFT);
//        break;
//    case WhereIsBall::RIGHT:
//        TextOutW(dc, 600, 600, L"Ball Position RIGHT", 20);
//        //PrintWhereIsBall(FVector2D::RIGHT);
//        break;
//    case WhereIsBall::NONE:
//    default:
//        TextOutW(dc, 600, 600, str.c_str(), static_cast<int>(str.size()));
//        break;
//    }
//
//   // WindowImage->ReleaseDC(dc);  // HDC�� ����//�츮���� ReleaseDC����
//}


struct Vec2 {
    float x, y;
};

// �� ���� �����ϴ� ���� ���� �Լ�
Vec2 createVector(const Vec2& from, const Vec2& to) 
{
    return { to.x - from.x, to.y - from.y };
}
// �� ������ ���� ��� �Լ�
float crossProduct(const Vec2& v1, const Vec2& v2) 
{
    return v1.x * v2.y - v1.y * v2.x;
}
//���������� ����-�������ҹ�
//���� ���ο� �������� ��ü �ﰢ���� ������ ���� �ﰢ�� ������ ������ ������ �������ִ�.
//���� �ܺο� ������, ���� ������ ���� ū�ﰢ������ ũ�ų�, �ﰢ�� ����� �����.

// �� P�� �ﰢ�� ABC ���ο� �ִ���
bool isPointInTriangle(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& P) 
{
    // �ﰢ�� ����
    Vec2 AB = createVector(A, B);
    Vec2 BC = createVector(B, C);
    Vec2 CA = createVector(C, A);
    // �������� ����
    Vec2 AP = createVector(A, P);
    Vec2 BP = createVector(B, P);
    Vec2 CP = createVector(C, P);
    // �������� ���� ���г����� ����
    float cross1 = crossProduct(AB, AP);
    float cross2 = crossProduct(BC, BP);
    float cross3 = crossProduct(CA, CP);
    // ������� ���� �Ǵ� 0�̻��� ���� ���°�,���ο� �����ʴٴ� ��
    return (cross1 > 0 && cross2 > 0 && cross3 > 0) || (cross1 < 0 && cross2 < 0 && cross3 < 0);
}




void APlayMap::Tick(float _DeltaTime)
{
    Vec2 Location = { 450, 450 };      // �簢���� ���� ��ġ (���� ��� ������)
    Vec2 Scale = { 300, 150 };         // �簢���� �ʺ�� ����

    // �簢���� ������
    Vec2 LeftTop = Location;
    Vec2 RightBot = { Location.x + Scale.x, Location.y + Scale.y };
    Vec2 Center = { Location.x + Scale.x / 2, Location.y + Scale.y / 2 };
    Vec2 TopRight = { RightBot.x, Location.y };
    Vec2 BottomLeft = { Location.x, RightBot.y };
    Vec2 BottomRight = { RightBot.x, RightBot.y };

    // �˻��� ��
    Vec2 P = { 475, 475 };

    // ���� ��ġ�� ������ ������ ����
    WhereIsBall BallPosition = WhereIsBall::NONE;

    // �� �ﰢ���� ���� �˻��ϰ� BallPosition�� ���� ����
    if (isPointInTriangle(LeftTop, Center, TopRight, P)) {
        BallPosition = WhereIsBall::UP;
    }
    else if (isPointInTriangle(BottomLeft, Center, BottomRight, P)) {
        BallPosition = WhereIsBall::DOWN;
    }
    else if (isPointInTriangle(LeftTop, Center, BottomLeft, P)) {
        BallPosition = WhereIsBall::LEFT;
    }
    else if (isPointInTriangle(TopRight, Center, BottomRight, P)) {
        BallPosition = WhereIsBall::RIGHT;
    }

    // ���� �α� - �׽�Ʈ �� ��ġ ���
    UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
    UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
    HDC dc = WindowImage->GetDC();  // HDC�� ������

    FVector2D BallPos = ABall::Pos; // Ball ��ġ
    std::wstring str = L"Pos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
    TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));

    // BallPosition�� ���� ���� �ؽ�Ʈ ���
    if (BallPosition == WhereIsBall::DOWN)
    {
        TextOutW(dc, 600, 600, L"Ball Position DOWN", 20);
    }
    else if (BallPosition == WhereIsBall::UP)
    {
        TextOutW(dc, 600, 600, L"Ball Position UP", 18);
    }
    else if (BallPosition == WhereIsBall::LEFT)
    {
        TextOutW(dc, 600, 600, L"Ball Position LEFT", 20);
    }
    else if (BallPosition == WhereIsBall::RIGHT)
    {
        TextOutW(dc, 600, 600, L"Ball Position RIGHT", 21);
    }
}


