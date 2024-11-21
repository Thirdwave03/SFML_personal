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

	std::unordered_map<int, sf::Vector2i> waypointMap;

public:
	int GetLife() { return life; }
	void SetLife(int life) { this->life = life; }

	int GetCoin() { return coin; }
	void SetCoin(int coin) { this->coin = coin; }

	void Init();
	void Reset();
	
	void SetWaypointMap();
	sf::Vector2i GetWaypointMap(int index);
	int GetWaypointCnt() { return waypointMap.size(); }
};

#define GAME_MGR (GameMgr::Instance())