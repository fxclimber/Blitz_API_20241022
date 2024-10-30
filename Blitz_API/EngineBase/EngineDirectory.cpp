#include "PreCompiledFile.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{
	// 만들어지면 현재로 
}

//UEnginePath 클래스를 상속받아 기본 생성자와 경로를 설정
UEngineDirectory::UEngineDirectory(std::string_view _Path)
	: UEnginePath(_Path)
{

}


UEngineDirectory::~UEngineDirectory()
{
}

//지정된 디렉터리 내 모든 파일을 리스트로 반환합니다. 
// 재귀적으로 하위 디렉터리까지 탐색할지 여부는 _IsRecursive 매개변수로 결정
std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive)
{
	std::vector<class UEngineFile> Result;

	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}

		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}

	return Result;
}


//특정 경로에서 모든 파일을 재귀적으로 탐색하고, 파일 리스트에 추가
void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path
	, std::vector<class UEngineFile>& _Result)
{
	// 경로를 넣어주면 그 경로의 첫번째 파일을 가리키게 된다.
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(_Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecursive(FilePath, _Result);
			++Diriter;
			continue;
		}

		_Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}
}