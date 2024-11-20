#pragma once

class DataTable
{
public:
	enum class Types
	{
		String,
		TileMap,
		Tower,
		Bug,
	};
	
	static const int noOfTypes = 1;


protected:
	Types type;


public:
	DataTable(Types t) : type(t) {}
	~DataTable() = default;
	DataTable(const DataTable& other) = default;
	DataTable& operator=(const DataTable& other) = default;

	virtual bool Load() = 0;
	virtual void Release() = 0;




};
