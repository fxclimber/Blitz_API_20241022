#include "PreCompiledFile.h"
#include "Level.h"
#include "EngineAPICore.h"
#include <string.h>
#include <Arkanoid_Contents/Ball.h>

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		if (nullptr != CurActor)
		{
			delete* StartIter;
		}
	}
}

void ULevel::Tick(float _DeltaTime)
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;
		CurActor->Tick(_DeltaTime);
	}
}

void ULevel::Render()
{
	ScreenClear();

	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;
		CurActor->Render();
	}
	DoubleBuffering();

	
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), 0, 0, Size.iX(), Size.iY());
}

void ULevel::DoubleBuffering()
{
	//레벨 렌더링 과정
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	FTransform Trans;
	Trans.Location = MainWindow.GetWindowSize().Half();
	Trans.Scale = MainWindow.GetWindowSize();

	// 백버퍼에 이미지 준비됬음.
	BackBufferImage->CopyToBit(WindowImage, Trans);

	// 은정 로그 - 테스트 볼위치 출력..
	FVector2D Pos = ABall::Pos;
	HDC dc=WindowImage->GetDC();

	std::wstring str = L"Pos : (" + std::to_wstring(Pos.X) + L", " + std::to_wstring(Pos.Y) + L")";
	TextOutW(dc, 100, 100, str.c_str(), static_cast<int>(str.size()));

}
