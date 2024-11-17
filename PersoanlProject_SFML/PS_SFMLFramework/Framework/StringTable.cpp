#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::wstring StringTable::Undefined = L"Undefined Id";

bool StringTable::Load() // csv 직접 파싱하지 않고 라이브러리 사용
{
	Release();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	//rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1)); // Get Column시 

	//for (int i = 0; i < doc.GetRowCount(); ++i)
	//{
	//	std::vector<std::string> strings = doc.GetRow<std::string>(i);
	//	// 행 갯수 맞추어 넘김, 쉼표로 구분된 모든 열의 데이터 vector로 저장
	//	auto it = table.find(strings[0]); // 0번째는 ID, 중복검사
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
		// GetRow 반환형 const 붙어서 &일 경우 const로 받아야함 (& 없으면 복사생성임에 무관)
		
		auto find = table.find(row[0]);
		if (find != table.end())
		{
			std::cout << "already exists" << std::endl;
			return false;
		}
		
		table[row[0]] = converter.from_bytes(row[1]);
	}
	return true;

	//for (int i = 0; i < docKor.GetRowCount(); i++) // 이하 4종 언어 row 수 같을 경우만 동작
	//{
	//	std::vector<std::string> strings = docKor.GetRow<std::string>(i);
	//	auto itKor = tableKor.find(strings[0]); // 0번째는 ID, 중복검사
	//	if (itKor != tableKor.end())
	//	{
	//		std::cout << "Korean string table key exists already" << std::endl;
	//		return false;
	//	}
	//	
	//	std::wstring& wstrKor = tableKor[strings[0]];
	//	wstrKor = converter.from_bytes(strings[1]);

	//	strings = docEng.GetRow<std::string>(i);
	//	auto itEng = tableEng.find(strings[0]); // 0번째는 ID, 중복검사
	//	if (itEng != tableEng.end())
	//	{
	//		std::cout << "English string table key exists already" << std::endl;
	//		return false;
	//	}

	//	std::wstring& wstrEng = tableEng[strings[0]];
	//	wstrEng = converter.from_bytes(strings[1]);

	//	strings = docJap.GetRow<std::string>(i);
	//	auto itJap = tableJap.find(strings[0]); // 0번째는 ID, 중복검사
	//	if (itJap != tableJap.end())
	//	{
	//		std::cout << "Japanese string table key exists already" << std::endl;
	//		return false;
	//	}

	//	std::wstring& wstrJap = tableJap[strings[0]];
	//	wstrJap = converter.from_bytes(strings[1]);

	//	strings = docChn.GetRow<std::string>(i);
	//	auto itChn = tableChn.find(strings[0]); // 0번째는 ID, 중복검사
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
//		return Undefined; // String table에 없는 아이디 리턴 요청한 것
//	}
//	return (find->second)[(int)lang]; // lang Index값에 해당하는 value
//	 // (find->second) = StringTable의 table Value 데이터형(wstring의 vector)
//	 // 해당 vector의 인덱스 (0~3) 각 Kor Eng Jap, Chn 들어감
//}

const std::wstring& StringTable::Get(const std::string& id)
{
	if (table.find(id) == table.end())
	{
		return Undefined; // String table에 없는 아이디 리턴 요청한 것
	}
	return table[id];
	
}
