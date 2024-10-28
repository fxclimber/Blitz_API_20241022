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
	// 반드시 호출해야함
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->OpenLevel("Play");
	//윈도우크기
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 900, 900 });

	// 윈도우 이름
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Blitz_Arkanoid");
}

void ArkanoidContentsCore::Tick()
{
}
