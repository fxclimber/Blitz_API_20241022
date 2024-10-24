#pragma once
#include <EngineCore/Actor.h>

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	void BeginPlay() override;
	void Tick() override;

protected:

private:

};

