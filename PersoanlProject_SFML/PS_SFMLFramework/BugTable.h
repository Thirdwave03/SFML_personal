#pragma once
#include "DataTable.h"
#include "Bug.h"

struct DataBug
{
	Bug::BugTypes bugType;					//  0
	std::string textureId;					//  1
	std::string bugName;					//  2

	int maxHp;								//  3
	float speed;							//  4
	int damage;								//  5
	int gold;								//  6
	float animationDuration;				//  7
	Bug::BugLayerType layerType;			//  8

	std::wstring description;				//  9
	std::wstring description2;				// 10
	std::wstring description3;				// 11
};

class BugTable : public DataTable
{
public:
	static DataBug Undefined;

protected:
	std::unordered_map<Bug::BugTypes, DataBug> table;
	std::string filePath = "tables/bug_table.csv";

public:
	BugTable() : DataTable(DataTable::Types::Bug) {}
	~BugTable() { Release(); }
	BugTable(const BugTable& other) = delete;
	BugTable& operator=(const BugTable& other) = delete;

	bool Load() override;
	void Release() override;

	const DataBug& Get(Bug::BugTypes type);

};