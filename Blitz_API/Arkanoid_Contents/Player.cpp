#include "PreCompiledFile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>

APlayer::APlayer()
{
	SetActorLocation({100,100});
	SetActorScale({100,100});
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	//�⺻ ũ�� ����
}

void APlayer::Tick(float _DeltaTime)
{
	{
		//sin�׽�Ʈ
		//// �ð��� ���� x, y ��ȭ�� offset�� ����
		//UEngineTimer timer = UEngineTimer();

		//float time = timer.GetDeltaTime();
		//float waveAmplitude = 100.0f; // ���� ũ��

		//FVector2D offset = FVector2D(waveAmplitude * std::sin(time), waveAmplitude * std::cos(time));

		//// ��ġ�� offset�� ���� ���� ȿ�� ����
		//FVector2D newPosition = GetActorLocation() + offset;
		//SetActorLocation(newPosition);

	}

	//Ÿ�̸� 
	AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
}
