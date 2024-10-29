#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>

//파일 관리하는 클래스
//ContentsCore 에서 사용
//폴더,경로,로드 - 리소스별 폴더 구분
//레벨전환시마다 리소스 언로드가 정석이지만,지금은 그 기능은 제외
class UEngineDirectory
{
public:
	UEngineDirectory();
	~UEngineDirectory();



protected:

private:
	std::filesystem::path FilePath;



};

