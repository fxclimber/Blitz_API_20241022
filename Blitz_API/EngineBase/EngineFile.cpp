#include "PreCompiledFile.h"
#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{


}

// 자식에서 부모 생성자를 명시적으로 호출해주면 된다.
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

//지정 경로의 파일을 주어진 모드(_Mode)로 열기,열기실패시 오류 
void UEngineFile::FileOpen(const char* _Mode)
{
	fopen_s(&File, Path, _Mode);

	if (nullptr == File)
	{
		MSGASSERT(Path /*+ "파일 오픈에 실패했습니다"*/);
	}
}

//파일이 열려있을때만, 데이타를 파일에 기록
void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("크기가 0인 데이터를 쓸수는 없습니다.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 사용하려고 했습니다.");
	}

	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
		return;
	}

	fwrite(_Ptr, _Size, 1, File);
}

//파일이 열려 있을 때만 데이터를 읽어 메모리에 복사
void UEngineFile::Read(void* _Ptr, size_t _Size)
{
	//포인터나 데이터 크기가 유효하지 않을 때도 예외를 처리
	if (0 == _Size)
	{
		MSGASSERT("크기가 0인 데이터를 읽을수는 없습니다.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("존재하지 않는 메모리를 읽으려고 했습니다.");
	}

	if (nullptr == File)
	{
		MSGASSERT("열지 않은 파일에 내용을 쓰려고 했습니다");
		return;
	}

	fread(_Ptr, _Size, 1, File);
}

// 인라인은 구현과 선언을분리하면 인라인을 하기 힘듭니다.
//파일 경로가 유효한지 확인하고, 파일이 존재하는지 여부를 반환
bool UEngineFile::IsExits()
{
	int Result = _access(Path, 00);

	return 0 == Result;
}

//파일이 열려 있는 경우 파일을 닫아 리소스를 해제하고, 포인터를 초기화
void UEngineFile::Close()
{
	// 방어코드
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

