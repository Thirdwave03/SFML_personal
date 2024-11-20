#pragma once
#include "GameObject.h"

class UiHud;

class IsometricTileMap : public GameObject
{
protected:
	sf::VertexArray vaTile;
	sf::VertexArray vaLineToBR;
	sf::VertexArray vaLineToBL;
	sf::Sprite selectedTile;

	sf::RenderStates vaTileRS;
	sf::RenderStates BRLineRS;
	sf::RenderStates BLLineRS;

	sf::Transform transform;
	std::string tileTexId = "graphics/V_sheet.png";
	sf::Vector2f tileSize = { 64.f,32.f };
	sf::Texture* texture = nullptr;
	sf::Vector2i tileCnt;

	UiHud* uiHud;
	
	std::unordered_map<int, std::vector<int>> tileTypeMap;

	bool isSelectable = false;
	bool isDebugMode = true;

	bool isMouseOnUi = false;

	bool isTileVisible = false;

public:
	IsometricTileMap();
	~IsometricTileMap() = default;

	bool SetIsoTile(std::unordered_map<int, std::vector<int>>& tileType, sf::Vector2i count, sf::Vector2f scale);

	void SetIsoLine();

	void SetScale(const sf::Vector2f& scale) override;

	void SetTileCnt(sf::Vector2i tileCnt);
	sf::Vector2i GetTileCnt() { return tileCnt; }

	sf::Vector2f GetIsoTileSize() { return tileSize; }

	void IndicateSelectedTile();
	bool TryBuild();

	void SetLoadedTileType(std::unordered_map<int, std::vector<int>>& tileMap);
	bool GetSelectable() { return isSelectable; }
	void TurnDebugMode();

	void GetUiHud(UiHud& uiHud) { this->uiHud = &uiHud; }
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	sf::FloatRect GetTileRect();

	void TurnTileVisible() { isTileVisible = !isTileVisible; }
};
