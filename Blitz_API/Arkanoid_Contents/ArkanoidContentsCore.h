#pragma once
#include <EngineCore/EngineAPICore.h>

class ArkanoidContentsCore : public UContentsCore
{
public:
	ArkanoidContentsCore();
	~ArkanoidContentsCore();

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel;

};

