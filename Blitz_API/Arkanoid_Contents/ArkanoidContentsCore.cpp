#include "PreCompiledFile.h"
#include "ArkanoidContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"

ArkanoidContentsCore::ArkanoidContentsCore()
{
}

ArkanoidContentsCore::~ArkanoidContentsCore()
{
}

void ArkanoidContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void ArkanoidContentsCore::Tick()
{
}
