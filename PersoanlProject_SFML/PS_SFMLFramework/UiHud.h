#pragma once
#include "GameObject.h"

class UiHud : public GameObject
{
protected:
    sf::Text mCoordsWorld;
    sf::Text mCoordsScreen;
	sf::Text mCoordsIso;
	sf::Text worldFloat;

	sf::Sprite buildButton;
	sf::CircleShape buildBoxCloseButton;

	sf::Sprite coinSprite;
	sf::Text coinText;

	sf::Sprite lifeSprite;
	sf::Text lifeText;

	sf::RectangleShape buildingMenu;
	sf::Sprite electricRocquet;
	sf::Sprite sprayF;
	sf::Sprite sprayR;
	sf::Sprite MosquitoRepellent;

	sf::Sprite clickedTower;
	
	TowerTypes buildingTower = TowerTypes::None;

	sf::Vector2f buildingIconScale = { 2.f,2.f };
	
    sf::Text forCalibrationCheck;

	bool isDebugMode = true;
	bool isBuildBoxOpen = false;
	bool isMouseOnUi = false;
	bool isBuilding = false;

	bool escPreventer = false;

public:
    UiHud(const std::string& name = "");
    ~UiHud() = default;
    UiHud(const UiHud& other) = default;
    UiHud& operator=(const UiHud& other) = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void TurnDebugMode();
	
	int GetBoolStatus();
	bool IfMouseOnUi() { return isMouseOnUi; }
	bool IfBuilding() { return isBuilding; }
	void UiMouseCheck();
	
	void OnBuilding();
	bool Build();

	TowerTypes GetBuildingTower() { return buildingTower; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void ResetDebugObjects();
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void UpdateDebugObjects(float dt);
	void Draw(sf::RenderWindow& window) override;
};

