#pragma once
#include <EngineCore/Actor.h>

enum class WhereIsBall
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class APlayMap : public AActor
{
public:
	APlayMap();
	~APlayMap();
	void Tick(float _DeltaTime) override;


public:
	int Where = static_cast<int>(WhereIsBall::NONE);

protected:

private:



};

