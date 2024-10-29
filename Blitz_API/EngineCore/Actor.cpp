#include "PreCompiledFile.h"
#include "Actor.h"
#include <EngineCore/EngineAPICore.h>

AActor::AActor()
{
}

AActor::~AActor()
{
}


void AActor::Render()
{
	{
		//                  100 100  - 50 50 => 50 50
		FVector2D LeftTop = Transform.Location - Transform.Scale.Half();
		//                  100 100  + 50 50 => 150 150
		FVector2D RightBot = Transform.Location + Transform.Scale.Half();


		UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
		UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
		HDC BackBufferDC = BackBufferImage->GetDC();
		Rectangle(BackBufferDC, LeftTop.iX(), LeftTop.iY(), RightBot.iX(), RightBot.iY());



	}


}