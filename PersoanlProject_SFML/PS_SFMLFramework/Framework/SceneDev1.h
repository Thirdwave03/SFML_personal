#pragma once
#include "Scene.h"
#include "IsometricTile.h"

class UiHud;

class SceneDev1 : public Scene
{
protected:
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;

	sf::FloatRect uiViewBorder;
	
	UiHud* uiHud;
	IsometricTile* isoTile;
	

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
};

