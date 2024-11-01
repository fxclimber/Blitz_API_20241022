#include "PreCompiledFile.h"
#include "ArkanoidContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "EndGameMode.h"
#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "Map_Play.h"
#include "Map_Title.h"
#include "Map_Ending.h"

ArkanoidContentsCore::ArkanoidContentsCore()
{
}

ArkanoidContentsCore::~ArkanoidContentsCore()
{
}

void ArkanoidContentsCore::BeginPlay()
{
	UEngineDirectory Dir;

	// Resources ���ϵ��� �������
	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
		return;
	}

	// ��� ���� �� ������
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	// �ڸ��� �۾� <- �ؽ��� ��� �ε��Ǿ���
	UImageManager::GetInst().CuttingSprite("Player_Right.png", { 128, 128 });

	{
		UEngineDirectory BombDir;
		BombDir.MoveParentToDirectory("Resources");
		BombDir.Append("bomb");

		UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());
	}

	// ������ 
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Blitz_Window");
	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });


	// CreateLevel
	//UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode,Map_Play>("Play");
	//UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, Map_Title>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, Map_Ending>("Ending");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void ArkanoidContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}