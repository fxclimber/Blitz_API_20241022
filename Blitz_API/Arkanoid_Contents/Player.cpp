#include "PreCompiledFile.h"
#include "Player.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"


APlayer::APlayer()
{
	SetActorLocation({450,450});
	SetActorScale({300,150});
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	//�⺻ ũ�� ����
	//���ε�,placeholders (�ܺ����� ����Ҷ�) �����,
	//UEngineInput::GetInst().BindAction('A', KeyEvent::Press, std::bind(&APlayer::MoveFunction,this,FVector2D::LEFT));
	//UEngineInput::GetInst().BindAction('D', KeyEvent::Press, std::bind(&APlayer::MoveFunction,this,FVector2D::RIGHT));
	//UEngineInput::GetInst().BindAction('S', KeyEvent::Press, std::bind(&APlayer::MoveFunction,this,FVector2D::DOWN));
	//UEngineInput::GetInst().BindAction('W', KeyEvent::Press, std::bind(&APlayer::MoveFunction,this,FVector2D::UP));
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
	//AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);

	//if (3.0f < UEngineInput::GetInst().IsPressTime(VK_LBUTTON))
	//{
	//	ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
	//	Ptr->SetActorLocation(GetActorLocation());
	//}

}

void APlayer::MoveFunction(FVector2D _Dir)
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	AddActorLocation(_Dir * DeltaTime * Speed);
}

