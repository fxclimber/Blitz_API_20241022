#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>

//���� �����ϴ� Ŭ����
//ContentsCore ���� ���
//����,���,�ε� - ���ҽ��� ���� ����
//������ȯ�ø��� ���ҽ� ��ε尡 ����������,������ �� ����� ����
class UEngineDirectory
{
public:
	UEngineDirectory();
	~UEngineDirectory();



protected:

private:
	std::filesystem::path FilePath;



};

