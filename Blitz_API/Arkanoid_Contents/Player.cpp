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
	//기본 크기 설정
}

void APlayer::Tick(float _DeltaTime)
{
	{
		//sin테스트
		//// 시간에 따른 x, y 변화를 offset에 저장
		//UEngineTimer timer = UEngineTimer();

		//float time = timer.GetDeltaTime();
		//float waveAmplitude = 100.0f; // 진폭 크기

		//FVector2D offset = FVector2D(waveAmplitude * std::sin(time), waveAmplitude * std::cos(time));

		//// 위치에 offset을 더해 물결 효과 적용
		//FVector2D newPosition = GetActorLocation() + offset;
		//SetActorLocation(newPosition);

	}

	//타이머 
	AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
}
