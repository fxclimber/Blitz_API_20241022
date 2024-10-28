#include "PreCompiledFile.h"
#include "Ball.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWinImage.h>
#include <EnginePlatform/EngineInput.h>

ABall::ABall()
{
	SetActorLocation({ 600,600});
	SetActorScale({ 40,40 });

}

ABall::~ABall()
{
}

void ABall::BeginPlay()
{
	//UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::LEFT));
	//UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::RIGHT));
	//UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::DOWN));
	//UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&ABall::MoveFunction, this, FVector2D::UP));

}



void ABall::MoveFunction(FVector2D _Dir)
{

	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	AddActorLocation(_Dir * DeltaTime * Speed);

}

//void ABall::Render()
//{
//	FVector2D LeftTop = Location - Scale.Half();
//	FVector2D RightBot = Location + Scale.Half();
//
//	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
//	HDC BackHDC = MainWindow.GetBackBuffer();
//
//	POINT diamondPoints[4] = {
//		{ Location.iX(), LeftTop.iY() },            // 상단
//		{ RightBot.iX(), Location.iY() },           // 오른쪽
//		{ Location.iX(), RightBot.iY() },           // 하단
//		{ LeftTop.iX(), Location.iY() }             // 왼쪽
//	};
//
//	// 마름모 그리기
//	Polygon(BackHDC, diamondPoints, 4);
//}

void ABall::Tick(float _DeltaTime)
{

	//if (3.0f < UEngineInput::GetInst().IsPressTime(VK_LBUTTON))
	//{
	//	SetActorLocation(GetActorLocation());
	//}

		if (true == UEngineInput::GetInst().IsPress('D'))
	{
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}

}