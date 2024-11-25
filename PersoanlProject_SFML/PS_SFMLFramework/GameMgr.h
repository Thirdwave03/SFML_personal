#pragma once

class GameMgr : public Singleton<GameMgr>
{
	friend Singleton<GameMgr>;

protected:
	GameMgr() = default;
	~GameMgr() = default;
	GameMgr(const GameMgr& other) = delete;
	GameMgr& operator=(const GameMgr& other) = delete;
	
	int life;
	int coin;
	int currentStage;
	int totalStage = 51;
	float hpMultiplier;

	bool isSpawning;


	std::unordered_map<int, sf::Vector2i> waypointMap;
	std::unordered_map<int, std::vector<int>> stageDataMap;	
	std::unordered_map<int, std::vector<int>> upgradableInfoMap;

public:
	int GetLife() { return life; }
	void SetLife(int life);

	int GetCoin() { return coin; }
	void SetCoin(int coin) { this->coin = coin; }
	void SpendCoin(int spendCoin) { this->coin -= spendCoin; }
	void AddCoin(int addCoin);
	void Init();
	void Reset();

	
	void SetWaypointMap();
	void SetStageDataMap();
	void SetUpgradableInfoMap();

	int GetCurrentStage() { return currentStage; }
	void SetCurrentStage(int stage);
	
	float GetHpMultiplier() { return hpMultiplier; }
	void SetHpMultiplier(float mtp) { hpMultiplier = mtp; }

	void SetStage0(); // for debug
	void SetStage1();
	void SetStage2();
	void SetStage3();
	void SetStage4();
	void SetStage5();
	void SetStage0to5();
	void SetStage6to10();
	void SetStage11to20();
	void SetStage21to30();
	void SetStage31to50();
	sf::Vector2i GetWaypointMap(int index);
	int GetWaypointCnt() { return waypointMap.size(); }
	std::vector<int> GetStageData(int index);
	int GetTotalStage() { return stageDataMap.size(); }
	int GetTotalStage2() { return totalStage; }
	std::vector<int> GetUpgradableInfo(int index);
};

#define GAME_MGR (GameMgr::Instance())