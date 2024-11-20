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
		table[id].towerType = (Towers::Types)std::stoi(row[0]);
		table[id].textureId = row[1];
		table[id].towerName = row[2];
		table[id].damage = std::stoi(row[3]);
		table[id].attackDuration = std::stof(row[4]);
		table[id].range = std::stof(row[5]);
		table[id].isAreaAttack = (bool)std::stoi(row[6]);
		table[id].price = std::stoi(row[7]);
		table[id].priceOnSell = std::stoi(row[8]);
		table[id].isUpgradable = (bool)std::stoi(row[9]);
		table[id].attackType = (Towers::AttackTypes)std::stoi(row[10]);
		table[id].bonusType = (Towers::AttackBonusTypes)std::stoi(row[11]);
		table[id].description = row[12];		
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
