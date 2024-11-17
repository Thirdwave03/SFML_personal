#pragma once
class DataTableMgr : public Singleton<DataTableMgr>
{
	friend Singleton<DataTableMgr>;
private:
	DataTableMgr() = default;
	~DataTableMgr();
	DataTableMgr(DataTableMgr& other) = delete;
	DataTableMgr& operator=(DataTableMgr& other) = delete;

	std::unordered_map<DataTable::Types, DataTable*> tables;

public:
	void Init();
	void Release();

	template<typename T>
	T* Get(DataTable::Types type);
};

// 싱글톤이 많으면 커플링이 많아짐, 유지보수에 불리함

template<typename T>
inline T* DataTableMgr::Get(DataTable::Types type)
{
	auto find = tables.find(type);
	if (find == tables.end())
	{
		return nullptr;
	}
	return dynamic_cast<T*>(find->second);
}

#define DATATABLE_MGR (DataTableMgr::Instance())
#define STRING_TABLE (DATATABLE_MGR.Get<StringTable>(DataTable::Types::String))
#define ZOMBIE_TABLE (DATATABLE_MGR.Get<ZombieTable>(DataTable::Types::Zombie))
#define ITEM_TABLE (DATATABLE_MGR.Get<ItemTable>(DataTable::Types::Item))
#define INT_TABLE (DATATABLE_MGR.Get<IntTable>(DataTable::Types::Int))