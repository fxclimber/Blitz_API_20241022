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
		//�׸�
		//                  100 100  - 50 50 => 50 50
		FVector2D LeftTop = Location - Scale.Half();
		//                  100 100  + 50 50 => 150 150
		FVector2D RightBot = Location + Scale.Half();


		UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
		HDC BackHDC = MainWindow.GetBackBuffer();

		Rectangle(BackHDC, LeftTop.iX(), LeftTop.iY(), RightBot.iX(), RightBot.iY());

	}


	{
		//������
		UEngineTimer timer = UEngineTimer();

		//float time = timer.GetDeltaTime();
		//float waveAmplitude = 100.0f; // ���� ũ��

		// �ð��� ���� x, y ��ȭ�� offset�� ����
		FVector2D offset = FVector2D(200,100);

		
		// �߽ɿ��� �»�, ���, ����, ���� �������� ���
		FVector2D LeftTop = FVector2D(Location.X - Scale.X * 0.5f, Location.Y) + offset;      // ���� �߰�
		FVector2D RightTop = FVector2D(Location.X, Location.Y - Scale.Y * 0.5f) + offset;     // ���� �߰�
		FVector2D RightBot = FVector2D(Location.X + Scale.X * 0.5f, Location.Y) + offset;     // ������ �߰�
		FVector2D LeftBot = FVector2D(Location.X, Location.Y + Scale.Y * 0.5f) + offset;      // �Ʒ��� �߰�

		// �� ������ ��ǥ�� �迭�� ����
		POINT diamondPoints[4] = {
			{ LeftTop.iX(), LeftTop.iY() },
			{ RightTop.iX(), RightTop.iY() },
			{ RightBot.iX(), RightBot.iY() },
			{ LeftBot.iX(), LeftBot.iY() }
		};

		// ������ �׸���
		UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
		HDC BackHDC = MainWindow.GetBackBuffer();

		// Polygon �Լ��� ����� ������ �׸��ϴ�.
		Polygon(BackHDC, diamondPoints, 4);

	}
}