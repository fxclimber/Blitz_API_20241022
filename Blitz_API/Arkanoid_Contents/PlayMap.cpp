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

    FVector2D Location = { 450, 450 }; // 사각형의 왼쪽 위 꼭짓점
    FVector2D Scale = { 300, 150 }; // 사각형의 크기 (너비, 높이)
    FVector2D Center = { Location.X + Scale.X / 2, Location.Y + Scale.Y / 2 };

    // 각 모서리 좌표
    FVector2D TopLeft = Location;
    FVector2D TopRight = { Location.X + Scale.X, Location.Y };
    FVector2D BottomLeft = { Location.X, Location.Y + Scale.Y };
    FVector2D BottomRight = { Location.X + Scale.X, Location.Y + Scale.Y };

    // 위치 판별 함수
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

    // 점이 속한 삼각형 위치 판별
    WhereIsBall position = DetermineTriangle(BallPos);

    // 은정 로그 - 테스트 볼위치 출력
    UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
    UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
    HDC dc = WindowImage->GetDC();  // HDC를 가져옴

    // 화면을 지우기 위한 작업 추가 (여기서 배경 색을 지우는 함수 필요)
    // 예: FillRect(dc, &rect, (HBRUSH)(COLOR_WINDOW + 1));  // rect는 전체 화면 영역

    std::wstring str = L"Pos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
    TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));

    // 삼각형 위치에 따라 동작 수행
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

   // WindowImage->ReleaseDC(dc);  // HDC를 해제//우리엔진 ReleaseDC없음
}
