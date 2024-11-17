#pragma once

class StringTable : public DataTable
{
public:
	static std::wstring Undefined;

protected:
	// <T1, T2>
	//	T1: 스트링 아이디
	//	T2: 언어별 스트링
	/*std::unordered_map<std::string, std::vector<std::wstring>> table;
	std::string filePath = "tables/string_table.csv";*/

	std::unordered_map<std::string, std::wstring> table;
	std::string filePathKor = "tables/string_table_Kor.csv";
	std::string filePathEng = "tables/string_table_Eng.csv";
	std::string filePathJap = "tables/string_table_Jap.csv";
	std::string filePathChn = "tables/string_table_Chn.csv";

public:
	StringTable() : DataTable(DataTable::Types::String) { };
	~StringTable() = default;

	bool Load() override;
	void Release() override;

	//const std::wstring& Get(const std::string& id);
	//const std::wstring& Get(const std::string& id, Languages lang);

	const std::wstring& Get(const std::string& id);
};

