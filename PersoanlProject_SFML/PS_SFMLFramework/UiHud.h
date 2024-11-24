#pragma once
#include "GameObject.h"

class Towers;

class UiHud : public GameObject
{
protected:
    sf::Text mCoordsWorld;
    sf::Text mCoordsScreen;
	sf::Text mCoordsIso;
	sf::Text worldFloat;

	sf::Sprite buildButton;
	sf::RectangleShape buildingMenu;
	sf::CircleShape buildBoxCloseButton;

	sf::Sprite electricRocquet;
	sf::Sprite sprayF;
	sf::Sprite sprayR;
	sf::Sprite MosquitoRepellent;
	
	sf::RectangleShape towerPurchaseGuideBox;
	sf::Text towerPurchaseGuideText;

	sf::RectangleShape towerBox;
	sf::CircleShape towerBoxCloseButton;
	sf::Text towerDescription;
	sf::Text towerDescription2;
	sf::Text towerDescription3;
	sf::Text textPageIndicator;
	sf::Sprite delKeySprite;
	sf::Sprite upgradableSprite1;
	sf::Sprite upgradableSprite2;
	std::vector<std::string> towerTextureIds;
	
	sf::RectangleShape upgradableGuideBox;
	sf::Text upgradableGuideText;

	sf::Sprite coinSprite;
	sf::Text coinText;

	sf::Sprite lifeSprite;
	sf::Text lifeText;

	sf::Sprite stageInfoButton;
	sf::RectangleShape stageInfoBox;
	sf::CircleShape stageInfoBoxCloseButton;
	sf::Text stageInfoText;

	sf::Sprite cockroach;
	sf::Sprite spider;
	sf::Sprite fly;
	sf::Sprite mosquito;

	bool isGameOver = false;
	sf::RectangleShape gameoverFadeOut;
	float gameoverFadeOutTimer = 4;
	sf::Text gameoverText;

	Towers::Types clickedTowerType;
	sf::Sprite clickedTower;
	Towers* selectedTower;
	
	Towers::Types buildingTower = Towers::Types::None;

	sf::Vector2f buildingIconScale = { 2.f,2.f };
	
	sf::RectangleShape blackBox;
    sf::Text centerMsg;

	bool isDebugMode = true;
	bool isBuildBoxOpen = false;
	bool isInfoBoxOpen = false;
	bool isMouseOnUi = false;
	bool isBuilding = false;
	bool isTowerSelected = false;
	bool isTowerDescriptionOpen = false;

	bool isInitialUiOn = true;
	bool isInfoBoxEverOpened = false;
	bool isBuildBoxEverOpened = false;

	bool isSettingBoxOn = false;

	float waveTimer = 30.f;
	bool isGameStart = false;

	int towerDescriptionPage = 0;
	int maxPage = 2; // 1 less number of actual pages
	int selectedTowerUpgradables = 0;

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
	void UiMouseCheckOnClick();
	
	void OnBuilding();
	bool Build();

	void OnVictory();

	void SetSelectedTower(Towers* tower);
	void SetNullSelectedTower();
	
	void OnTowerSelect();
	void UpdateTowerDescription();

	bool IsInitUiOpen() { return isInitialUiOn; }

	Towers::Types GetBuildingTower() { return buildingTower; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void SetTowerTextureIds();
	void ResetDebugObjects();
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void UpdateDebugObjects(float dt);
	void Draw(sf::RenderWindow& window) override;
};

