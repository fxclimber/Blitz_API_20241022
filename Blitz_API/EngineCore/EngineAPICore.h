#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")


class UEngineAPICore
{
public:
	UEngineAPICore();
	~UEngineAPICore();

	//������ ���۽�ų �Լ�
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

	static UEngineAPICore* MainCore;//�ڽ��� �������������� �����ִ�

	UEngineWindow EngineMainWindow; //���� ���� ������
	//���ӽ��ൿ�� ��� �� �Լ�
	void Tick();
	void Render();


};

