#pragma once
#include "DataTable.h"

class TileTable : public DataTable
{
public:
	static int UndefinedTileType;

protected:
	std::unordered_map<int, std::vector<int>> table;
	std::string filePathDefault = "tables/tile_table_default.csv";
	std::string filePathStage1 = "tables/tile_table_stage1.csv";
	std::string filePathStage2 = "tables/tile_table_stage2.csv";
	std::string filePathStage3 = "tables/tile_table_stage3.csv";
	
	int currentFileRowCnt = 0;
	int currentFileColumnCnt = 0;

public:
	TileTable() : DataTable(DataTable::Types::TileMap) { };
	~TileTable() = default;

	bool Load() override;
	void Release() override;
	sf::Vector2i GetTileMapCount();
	std::unordered_map<int, std::vector<int>>& GetTileMapTable();

	const int& Get(int column, int row);
};

