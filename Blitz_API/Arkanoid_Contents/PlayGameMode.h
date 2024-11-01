#pragma once
#include <EngineCore/GameMode.h>

class APlayGameMode : public AGameMode
{
public:
	APlayGameMode();
	~APlayGameMode();
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:


};

