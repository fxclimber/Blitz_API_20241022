#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")


class UEngineAPICore
{
public:
	UEngineAPICore();
	~UEngineAPICore();

	//게임을 시작시킬 함수
	static int EngineStart(HINSTANCE _Inst);

	class UEngineAPICore* GetCore()
	{
		return MainCore;
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}



protected:

private:
	static void EngineLoop();

	static UEngineAPICore* MainCore;//자신을 포인터전역으로 갖고있다

	UEngineWindow EngineMainWindow; //엔진 메인 윈도우
	//게임실행동안 계속 돌 함수
	void Tick();
	void Render();


};

