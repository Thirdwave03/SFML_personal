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

	//for (int i = 0; i < docKor.GetRowCount(); i++) // ���� 4�� ��� row �� ���� ��츸 ����
	//{
	//	std::vector<std::string> strings = docKor.GetRow<std::string>(i);
	//	auto itKor = tableKor.find(strings[0]); // 0��°�� ID, �ߺ��˻�
	//	if (itKor != tableKor.end())
	//	{
	//		std::cout << "Korean string table key exists already" << std::endl;
	//		return false;
	//	}
	//	
	//	std::wstring& wstrKor = tableKor[strings[0]];
	//	wstrKor = converter.from_bytes(strings[1]);

	//	strings = docEng.GetRow<std::string>(i);
	//	auto itEng = tableEng.find(strings[0]); // 0��°�� ID, �ߺ��˻�
	//	if (itEng != tableEng.end())
	//	{
	//		std::cout << "English string table key exists already" << std::endl;
	//		return false;
	//	}

	//	std::wstring& wstrEng = tableEng[strings[0]];
	//	wstrEng = converter.from_bytes(strings[1]);

	//	strings = docJap.GetRow<std::string>(i);
	//	auto itJap = tableJap.find(strings[0]); // 0��°�� ID, �ߺ��˻�
	//	if (itJap != tableJap.end())
	//	{
	//		std::cout << "Japanese string table key exists already" << std::endl;
	//		return false;
	//	}

	//	std::wstring& wstrJap = tableJap[strings[0]];
	//	wstrJap = converter.from_bytes(strings[1]);

	//	strings = docChn.GetRow<std::string>(i);
	//	auto itChn = tableChn.find(strings[0]); // 0��°�� ID, �ߺ��˻�
	//	if (itChn != tableChn.end())
	//	{
	//		std::cout << "Chinese string table key exists already" << std::endl;
	//		return false;
	//	}

	//	std::wstring& wstrChn = tableChn[strings[0]];
	//	wstrChn = converter.from_bytes(strings[1]);
	//}

	//return true;
}

void StringTable::Release()
{
	table.clear();
}

//const std::wstring& StringTable::Get(const std::string& id)
//{
//	return Get(id, Variables::currentLang);
//}

//const std::wstring& StringTable::Get(const std::string& id, Languages lang)
//{
//	auto find = table.find(id);
//	if (find == table.end())
//	{
//		return Undefined; // String table�� ���� ���̵� ���� ��û�� ��
//	}
//	return (find->second)[(int)lang]; // lang Index���� �ش��ϴ� value
//	 // (find->second) = StringTable�� table Value ��������(wstring�� vector)
//	 // �ش� vector�� �ε��� (0~3) �� Kor Eng Jap, Chn ��
//}

const std::wstring& StringTable::Get(const std::string& id)
{
	if (table.find(id) == table.end())
	{
		return Undefined; // String table�� ���� ���̵� ���� ��û�� ��
	}
	return table[id];
	
}
