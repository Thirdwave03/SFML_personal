#pragma once
#include "DataTable.h"
#include "Towers.h"

struct DataTower
{
	Towers::Types towerType;				//  0
	std::string textureId;					//  1
	std::string towerName;					//  2

	int damage;								//  3
	float attackDuration;					//  4
	float range;							//  5
	bool isAreaAttack;						//  6

	int price;								//  7
	int priceOnSell;						//  8

	int upgradableTowers;						//  9

	Towers::AttackTypes attackType;			// 10
	Towers::AttackBonusTypes bonusType;		// 11

	std::wstring description;				// 12
	std::wstring description2;				// 13
	std::wstring description3;				// 14
};

class TowerTable : public DataTable
{
public:
	static DataTower Undefined;

protected:
	std::unordered_map<Towers::Types, DataTower> table;
	std::string filePath = "tables/tower_table.csv";

public:
	TowerTable() : DataTable(DataTable::Types::Tower) {}
	~TowerTable() { Release(); }
	TowerTable(const TowerTable& other) = delete;
	TowerTable& operator=(const TowerTable& other) = delete;

	bool Load() override;
	void Release() override;

	const DataTower& Get(Towers::Types type);

};