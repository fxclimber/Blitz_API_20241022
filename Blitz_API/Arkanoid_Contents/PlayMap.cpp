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
//    FVector2D Location = { 450, 450 }; // 사각형의 왼쪽 위 꼭짓점
//    FVector2D Scale = { 300, 150 }; // 사각형의 크기 (너비, 높이)
//    FVector2D Center = { Location.X + Scale.X / 2, Location.Y + Scale.Y / 2 };
//
//    // 각 모서리 좌표
//    FVector2D TopLeft = Location;
//    FVector2D TopRight = { Location.X + Scale.X, Location.Y };
//    FVector2D BottomLeft = { Location.X, Location.Y + Scale.Y };
//    FVector2D BottomRight = { Location.X + Scale.X/2, Location.Y + Scale.Y };
//
//    // 위치 판별 함수
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
//    // 점이 속한 삼각형 위치 판별
//    WhereIsBall position = DetermineTriangle(BallPos);
//
//    // 은정 로그 - 테스트 볼위치 출력
//    UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
//    UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
//    HDC dc = WindowImage->GetDC();  // HDC를 가져옴
//
//    // 화면을 지우기 위한 작업 추가 (여기서 배경 색을 지우는 함수 필요)
//    // 예: FillRect(dc, &rect, (HBRUSH)(COLOR_WINDOW + 1));  // rect는 전체 화면 영역
//
//    std::wstring str = L"Pos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
//    TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));
//
//    // 삼각형 위치에 따라 동작 수행
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
//   // WindowImage->ReleaseDC(dc);  // HDC를 해제//우리엔진 ReleaseDC없음
//}


struct Vec2 {
    float x, y;
};

// 두 점을 연결하는 벡터 생성 함수
Vec2 createVector(const Vec2& from, const Vec2& to) 
{
    return { to.x - from.x, to.y - from.y };
}
// 두 벡터의 외적 계산 함수
float crossProduct(const Vec2& v1, const Vec2& v2) 
{
    return v1.x * v2.y - v1.y * v2.x;
}
//면적보존의 원리-면적분할법
//점이 내부에 있을때만 전체 삼각형의 면적을 작은 삼각형 세개의 면적의 합으로 나눌수있다.
//점이 외부에 있을때, 나눈 면적의 함은 큰삼각형보다 크거나, 삼각형 모양을 벗어난다.

// 점 P가 삼각형 ABC 내부에 있는지
bool isPointInTriangle(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& P) 
{
    // 삼각형 선분
    Vec2 AB = createVector(A, B);
    Vec2 BC = createVector(B, C);
    Vec2 CA = createVector(C, A);
    // 중점과의 선분
    Vec2 AP = createVector(A, P);
    Vec2 BP = createVector(B, P);
    Vec2 CP = createVector(C, P);
    // 꼭지점이 닿은 선분끼리의 외적
    float cross1 = crossProduct(AB, AP);
    float cross2 = crossProduct(BC, BP);
    float cross3 = crossProduct(CA, CP);
    // 결과값이 음수 또는 0이상의 값이 나온건,내부에 있지않다는 뜻
    return (cross1 > 0 && cross2 > 0 && cross3 > 0) || (cross1 < 0 && cross2 < 0 && cross3 < 0);
}




void APlayMap::Tick(float _DeltaTime)
{
    Vec2 Location = { 450, 450 };      // 사각형의 시작 위치 (왼쪽 상단 꼭짓점)
    Vec2 Scale = { 300, 150 };         // 사각형의 너비와 높이

    // 사각형의 꼭짓점
    Vec2 LeftTop = Location;
    Vec2 RightBot = { Location.x + Scale.x, Location.y + Scale.y };
    Vec2 Center = { Location.x + Scale.x / 2, Location.y + Scale.y / 2 };
    Vec2 TopRight = { RightBot.x, Location.y };
    Vec2 BottomLeft = { Location.x, RightBot.y };
    Vec2 BottomRight = { RightBot.x, RightBot.y };

    // 검사할 점
    Vec2 P = { 475, 475 };

    // 점의 위치를 저장할 열거형 변수
    WhereIsBall BallPosition = WhereIsBall::NONE;

    // 각 삼각형에 대해 검사하고 BallPosition에 값을 설정
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

    // 은정 로그 - 테스트 볼 위치 출력
    UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
    UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
    HDC dc = WindowImage->GetDC();  // HDC를 가져옴

    FVector2D BallPos = ABall::Pos; // Ball 위치
    std::wstring str = L"Pos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
    TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));

    // BallPosition의 값에 따라 텍스트 출력
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


