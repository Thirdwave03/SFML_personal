#pragma once
#include "Scene.h"
#include "IsometricTileMap.h"

class UiHud;
class TowerBuildMgr;
class Towers;

class SceneDev1 : public Scene
{
protected:
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;

	sf::FloatRect uiViewBorder;

	UiHud* uiHud;
	IsometricTileMap* isoTile;

	std::list<Towers*> towers;
	ObjectPool<Towers> towerPool;

	TowerBuildMgr* towerBuildMgr;

public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetIsoTileSize();
	sf::Vector2f GetIsoTileScale();

	void BuildTower();
};

