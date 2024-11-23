#pragma once
#include "Scene.h"
#include "IsometricTileMap.h"

class UiHud;
class TowerBuildMgr;
class Towers;
class Bug;
class BugDieEffect;

class SceneDev1 : public Scene
{
protected:

	UiHud* uiHud;
	IsometricTileMap* isoTile;

	std::list<Towers*> towers;
	ObjectPool<Towers> towerPool;

	std::list<Bug*> bugs;
	ObjectPool<Bug> bugPool;

	std::list<BugDieEffect*> bugDieEffects;
	ObjectPool<BugDieEffect> bugDieEffectPool;

	Towers* selectedTower;

	std::queue<int> spawnQueue;

	bool isSpawning;
	int spawnCnt;
	const float spawnDuration = 0.6;
	float spawnTimer;

public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnClickLeft();
	void OnClickRight();

	sf::Vector2f GetIsoTileSize();
	sf::Vector2f GetIsoTileScale();
	
	const std::list<Bug*>& GetBugList() { return bugs; }
	
	void BuildTower();
	void OnTowerSold(sf::Vector2i isoCoord);

	void SpawnBugTest(int cnt, int num = 1, float duration = 1.f);
	void SpawnBug(int bugTypeId);

	void SetWaveSpawnQueue();

	void CallBugDieEffect(sf::Vector2f pos);
	
};

