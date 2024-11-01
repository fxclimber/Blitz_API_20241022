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

	// ���� ���� �ִ�
	{
		UEngineDirectory BombDir;
		BombDir.MoveParentToDirectory("Resources");
		BombDir.Append("bomb");

		UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());
	}


	// ����- �е�ִ� �׽�Ʈ
	{
		//paddle_materialize
		UEngineDirectory paddle_materialize;
		paddle_materialize.MoveParentToDirectory("Resources");
		paddle_materialize.Append("paddle_materialize");

		UImageManager::GetInst().LoadFolder(paddle_materialize.GetPathToString());
	}
	{
		//paddle_laser
		//UEngineDirectory paddle_laser;
		//paddle_laser.MoveParentToDirectory("Resources");
		//paddle_laser.Append("paddle_laser");

		//UImageManager::GetInst().LoadFolder(paddle_laser.GetPathToString());
	}
	{
		//powerup_catch
		//UEngineDirectory powerup_catch;
		//powerup_catch.MoveParentToDirectory("Resources");
		//powerup_catch.Append("powerup_catch");

		//UImageManager::GetInst().LoadFolder(powerup_catch.GetPathToString());
	}
	{
		//enemy_molecule
		//UEngineDirectory enemy_molecule;
		//enemy_molecule.MoveParentToDirectory("Resources");
		//enemy_molecule.Append("enemy_molecule");

		//UImageManager::GetInst().LoadFolder(enemy_molecule.GetPathToString());
	}



	// ������ 
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Blitz_Window");
	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 800, 900 });


	// CreateLevel
	//UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode,Map_Play>("Play");
	//UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, Map_Title>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AEndGameMode, Map_Ending>("Ending");

	UEngineAPICore::GetCore()->OpenLevel("Title");

}

void ArkanoidContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}