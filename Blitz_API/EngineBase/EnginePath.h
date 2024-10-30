#pragma once
#include <filesystem>

//파일 또는 디렉터리 경로를 관리하고 다양한 경로 작업을 수행
class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	bool IsExists();
	void MoveParent();

	std::string GetPathToString();

	// 파일명 + 확장자 포함
	std::string GetFileName();

	// 확장자
	std::string GetExtension();


	bool MoveParentToDirectory(std::string_view _Path);

	bool IsDirectory();

	bool IsFile();


protected:
	std::filesystem::path Path;

private:
};

