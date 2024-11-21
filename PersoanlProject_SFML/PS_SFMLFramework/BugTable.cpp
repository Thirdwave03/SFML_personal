#include "stdafx.h"
#include "BugTable.h"
#include "rapidcsv.h"

DataBug BugTable::Undefined;

bool BugTable::Load()
{
	Release();

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		Bug::BugTypes id = (Bug::BugTypes)std::stoi(row[0]);
		if (table.find(id) != table.end())
		{
			std::cout << "tower table key exists already" << std::endl;
			return false;
		}		
		table[id].bugType = (Bug::BugTypes)std::stoi(row[0]);
		table[id].textureId = row[1];
		table[id].bugName = row[2];
		table[id].maxHp = std::stoi(row[3]);
		table[id].speed = std::stof(row[4]);
		table[id].damage = std::stoi(row[5]);
		table[id].gold = std::stoi(row[6]);
		table[id].animationDuration = std::stof(row[7]);
		table[id].layerType = (Bug::BugLayerType)std::stoi(row[8]);
		table[id].description = converter.from_bytes(row[9]);
		table[id].description2 = converter.from_bytes(row[10]);
		table[id].description3 = converter.from_bytes(row[11]);
	}
	return true;
}

void BugTable::Release()
{
}

const DataBug& BugTable::Get(Bug::BugTypes type)
{
	auto find = table.find(type);
	if (find == table.end())
		return Undefined;
	else
		return find->second;
}
