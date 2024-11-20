#include "stdafx.h"
#include "TowerTable.h"
#include "rapidcsv.h"

DataTower TowerTable::Undefined;

bool TowerTable::Load()
{
	Release();

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		auto row = doc.GetRow<std::string>(i);
		Towers::Types id = (Towers::Types)std::stoi(row[0]);
		if (table.find(id) != table.end())
		{
			std::cout << "tower table key exists already" << std::endl;
			return false;
		}

		/*table[id].
		*/
	}

	return true;
}

void TowerTable::Release()
{
}

const DataTower& TowerTable::Get(Towers::Types type)
{
	auto find = table.find(type);
	if (find == table.end())
		return Undefined;
	else
		return find->second;
}
