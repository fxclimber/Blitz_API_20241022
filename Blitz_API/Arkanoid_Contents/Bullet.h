#pragma once
#include <EngineCore/Actor.h>

class ABullet : public AActor
{
public:
	ABullet();
	~ABullet();


protected:
	void Tick(float _DeltaTime) override;


private:
};

