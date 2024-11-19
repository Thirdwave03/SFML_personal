#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::wstring StringTable::Undefined = L"Undefined Id";

bool StringTable::Load() // csv ���� �Ľ����� �ʰ� ���̺귯�� ���
{
	Release();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	//rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1)); // Get Column�� 

	//for (int i = 0; i < doc.GetRowCount(); ++i)
	//{
	//	std::vector<std::string> strings = doc.GetRow<std::string>(i);
	//	// �� ���� ���߾� �ѱ�, ��ǥ�� ���е� ��� ���� ������ vector�� ����
	//	auto it = table.find(strings[0]); // 0��°�� ID, �ߺ��˻�
	//	if (it != table.end())
	//	{
	//		std::cout << "string table key exists already" << std::endl;
	//		return false;
	//	}

	//	for (int j = 1; j <= (int)Languages::Count; ++j)
	//	{
	//		std::vector<std::wstring>& vec = table[strings[0]]; // Key - ID
	//		//vec.resize((int)Languages::Count);
	//		//vec[j] = converter.from_bytes(strings[j + 1]);
	//		vec.push_back(converter.from_bytes(strings[j]));
	//	}
	//}

	rapidcsv::Document doc;

	switch (Variables::currentLang)
	{
	case Languages::Korean:
		doc.Load(filePathKor, rapidcsv::LabelParams(0, -1));
		break;
	case Languages::English:
		doc.Load(filePathEng, rapidcsv::LabelParams(0, -1));
		break;
	case Languages::Japanese:
		doc.Load(filePathJap, rapidcsv::LabelParams(0, -1));
		break;
	case Languages::Chinese:
		doc.Load(filePathChn, rapidcsv::LabelParams(0, -1));
		break;
	default:
		return false;
		break;
	}

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		const std::vector<std::string>& row = doc.GetRow<std::string>(i);
		// GetRow ��ȯ�� const �پ &�� ��� const�� �޾ƾ��� (& ������ ��������ӿ� ����)
		
		auto find = table.find(row[0]);
		if (find != table.end())
		{
			std::cout << "already exists" << std::endl;
			return false;
		}
		
		table[row[0]] = converter.from_bytes(row[1]);
	}
	return true;
}

void StringTable::Release()
{
	table.clear();
}

const std::wstring& StringTable::Get(const std::string& id)
{
	if (table.find(id) == table.end())
	{
		return Undefined; // String table�� ���� ���̵� ���� ��û�� ��
	}
	return table[id];
	
}
