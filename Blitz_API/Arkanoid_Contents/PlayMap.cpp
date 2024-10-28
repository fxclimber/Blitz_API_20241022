#include "PreCompiledFile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>


UPlayMap::UPlayMap()
{
	SetActorScale({ 1200,800 });
	SetActorLocation({ 600,400 });
}

UPlayMap::~UPlayMap()
{
}

void UPlayMap::Render()
{
	//{
	//	//마름모
	//	//UEngineTimer timer = UEngineTimer();

	//	//float time = timer.GetDeltaTime();
	//	//float waveAmplitude = 100.0f; // 진폭 크기

	//	// 시간에 따른 x, y 변화를 offset에 저장
	//	FVector2D offset = FVector2D(200, 100);


	//	// 중심에서 좌상, 우상, 우하, 좌하 꼭짓점을 계산
	//	FVector2D LeftTop = FVector2D(Location.X - Scale.X * 0.5f, Location.Y) + offset;      // 왼쪽 중간
	//	FVector2D RightTop = FVector2D(Location.X, Location.Y - Scale.Y * 0.5f) + offset;     // 위쪽 중간
	//	FVector2D RightBot = FVector2D(Location.X + Scale.X * 0.5f, Location.Y) + offset;     // 오른쪽 중간
	//	FVector2D LeftBot = FVector2D(Location.X, Location.Y + Scale.Y * 0.5f) + offset;      // 아래쪽 중간

	//	// 각 꼭짓점 좌표를 배열로 생성
	//	POINT diamondPoints[4] = {
	//		{ LeftTop.iX(), LeftTop.iY() },
	//		{ RightTop.iX(), RightTop.iY() },
	//		{ RightBot.iX(), RightBot.iY() },
	//		{ LeftBot.iX(), LeftBot.iY() }
	//	};

	//	// 마름모 그리기
	//	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	//	HDC BackHDC = MainWindow.GetBackBuffer();

	//	// Polygon 함수를 사용해 마름모를 그립니다.
	//	Polygon(BackHDC, diamondPoints, 4);

	//}

}
