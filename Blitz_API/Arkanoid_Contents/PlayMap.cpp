#include "PreCompiledFile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineMath.h>
#include "Ball.h"
#include <iostream>
#include <EnginePlatform/EngineWinImage.h>
#include "Bullet.h"

#include <EngineCore/SpriteRenderer.h>


APlayMap::APlayMap()
{
	ballEnum = WhereIsBall::NONE;
	SetActorLocation({ 450,450 });
	SetActorScale({ 300, 150 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("characters.png");
	SpriteRenderer->SetComponentScale({ 100, 100 });

}

APlayMap::~APlayMap()
{
}

void APlayMap::Tick(float _DeltaTime)
{
	FVector2D BallPos = ABall::Pos;
	FVector2D Pos = GetActorLocation();
	FVector2D Scale = { 300, 150 };

	FVector2D LeftTop = Pos - Scale.Half();
	FVector2D RightBot = Pos + Scale.Half();

	FVector2D DiffPos = BallPos - Pos;

	// 은정 로그 - 테스트 볼위치 출력
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	HDC dc = WindowImage->GetDC();  // HDC를 가져옴
	std::wstring str = L"BallPos : (" + std::to_wstring(BallPos.X) + L", " + std::to_wstring(BallPos.Y) + L")";
	TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));


	// 애초에 사각형에 들어오지 않았다면

	if (0 < DiffPos.X && DiffPos.X < Scale.X && DiffPos.Y >0 && DiffPos.Y < Scale.Y /2)
	{
		ballEnum = WhereIsBall::UP;
	}
	else if (0 < DiffPos.X && DiffPos.X < Scale.X && DiffPos.Y > Scale.Y/2 && DiffPos.Y < Scale.Y)
	{
		ballEnum = WhereIsBall::DOWN;
	}
	else if (0 < DiffPos.X && DiffPos.X < Scale.X / 2 && DiffPos.Y >0 && DiffPos.Y < Scale.Y)
	{
		ballEnum = WhereIsBall::LEFT;
	}
	else if(Scale.X/2 < DiffPos.X && DiffPos.X < Scale.X && DiffPos.Y >0 && DiffPos.Y < Scale.Y)
	{
		ballEnum = WhereIsBall::RIGHT;
	}
	else
	{
		ballEnum = WhereIsBall::NONE;
	}


	switch (ballEnum)
	{
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
	default:
		TextOutW(dc, 600, 600, L"Ball Position NONE", 20);
		break;
	}

}

