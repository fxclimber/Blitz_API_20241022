#include "PreCompiledFile.h"
#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{


}

// �ڽĿ��� �θ� �����ڸ� ��������� ȣ�����ָ� �ȴ�.
UEngineFile::UEngineFile(std::string_view _Path)
	: UEnginePath(_Path)
{

}

UEngineFile::UEngineFile(std::filesystem::path _Path)
	: UEnginePath(_Path)
{

}

UEngineFile::~UEngineFile()
{
	Close();
}

//���� ����� ������ �־��� ���(_Mode)�� ����,������н� ���� 
void UEngineFile::FileOpen(const char* _Mode)
{
	fopen_s(&File, Path, _Mode);

	if (nullptr == File)
	{
		MSGASSERT(Path /*+ "���� ���¿� �����߽��ϴ�"*/);
	}
}

//������ ������������, ����Ÿ�� ���Ͽ� ���
void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("ũ�Ⱑ 0�� �����͸� ������ �����ϴ�.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("�������� �ʴ� �޸𸮸� ����Ϸ��� �߽��ϴ�.");
	}

	if (nullptr == File)
	{
		MSGASSERT("���� ���� ���Ͽ� ������ ������ �߽��ϴ�");
		return;
	}

	fwrite(_Ptr, _Size, 1, File);
}

//������ ���� ���� ���� �����͸� �о� �޸𸮿� ����
void UEngineFile::Read(void* _Ptr, size_t _Size)
{
	//�����ͳ� ������ ũ�Ⱑ ��ȿ���� ���� ���� ���ܸ� ó��
	if (0 == _Size)
	{
		MSGASSERT("ũ�Ⱑ 0�� �����͸� �������� �����ϴ�.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("�������� �ʴ� �޸𸮸� �������� �߽��ϴ�.");
	}

	if (nullptr == File)
	{
		MSGASSERT("���� ���� ���Ͽ� ������ ������ �߽��ϴ�");
		return;
	}

	fread(_Ptr, _Size, 1, File);
}

// �ζ����� ������ �������и��ϸ� �ζ����� �ϱ� ����ϴ�.
//���� ��ΰ� ��ȿ���� Ȯ���ϰ�, ������ �����ϴ��� ���θ� ��ȯ
bool UEngineFile::IsExits()
{
	int Result = _access(Path, 00);

	return 0 == Result;
}

//������ ���� �ִ� ��� ������ �ݾ� ���ҽ��� �����ϰ�, �����͸� �ʱ�ȭ
void UEngineFile::Close()
{
	// ����ڵ�
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

