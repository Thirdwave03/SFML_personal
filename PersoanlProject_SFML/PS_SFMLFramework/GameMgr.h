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

	

public:
	int GetLife() { return life; }
	void SetLife(int life) { this->life = life; }

	int GetCoin() { return coin; }
	void SetCoin(int coin) { this->coin = coin; }

	void Init();
	void Reset();
	
};

#define GAME_MGR (GameMgr::Instance())