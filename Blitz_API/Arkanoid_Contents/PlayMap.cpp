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
	//	//������
	//	//UEngineTimer timer = UEngineTimer();

	//	//float time = timer.GetDeltaTime();
	//	//float waveAmplitude = 100.0f; // ���� ũ��

	//	// �ð��� ���� x, y ��ȭ�� offset�� ����
	//	FVector2D offset = FVector2D(200, 100);


	//	// �߽ɿ��� �»�, ���, ����, ���� �������� ���
	//	FVector2D LeftTop = FVector2D(Location.X - Scale.X * 0.5f, Location.Y) + offset;      // ���� �߰�
	//	FVector2D RightTop = FVector2D(Location.X, Location.Y - Scale.Y * 0.5f) + offset;     // ���� �߰�
	//	FVector2D RightBot = FVector2D(Location.X + Scale.X * 0.5f, Location.Y) + offset;     // ������ �߰�
	//	FVector2D LeftBot = FVector2D(Location.X, Location.Y + Scale.Y * 0.5f) + offset;      // �Ʒ��� �߰�

	//	// �� ������ ��ǥ�� �迭�� ����
	//	POINT diamondPoints[4] = {
	//		{ LeftTop.iX(), LeftTop.iY() },
	//		{ RightTop.iX(), RightTop.iY() },
	//		{ RightBot.iX(), RightBot.iY() },
	//		{ LeftBot.iX(), LeftBot.iY() }
	//	};

	//	// ������ �׸���
	//	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	//	HDC BackHDC = MainWindow.GetBackBuffer();

	//	// Polygon �Լ��� ����� ������ �׸��ϴ�.
	//	Polygon(BackHDC, diamondPoints, 4);

	//}

}
