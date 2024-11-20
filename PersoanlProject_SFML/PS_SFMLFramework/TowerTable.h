#pragma once
#include "DataTable.h"
#include "Towers.h"

struct DataTower
{
	int damage;
	float attackDuration;
	float range;
	bool isAreaAttack;

	int price;

	bool isConstructable;

	Towers::AttackTypes attackType;
	Towers::AttackBonusTypes bonusType;

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