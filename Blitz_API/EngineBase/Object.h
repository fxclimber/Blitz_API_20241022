#pragma once
#include <string>

// ���� :
class UObject
{
public:
	// constrcuter destructer
	UObject();

	// Ȥ���� �ڽĵ��� �Ҹ��ڰ� ȣ�� �ȵǴ� ��츦 ����������
	// �����Լ� ���̺��� ���� ���̹Ƿ� �ظ��ϸ� �ڽ����� �Ҹ��ڰ� ȣ��ȵǴ� ���� ���� ���̴�.
	virtual ~UObject();

	// �̸� �����Ҷ� ���� �ϰ� ������ �������̵���.
	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

protected:

private:
	std::string Name;

};

