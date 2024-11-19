#pragma once
#include "GameObject.h"

class IsometricTileMap : public GameObject
{
protected:
	sf::VertexArray vaTile;
	sf::VertexArray vaLineToBR;
	sf::VertexArray vaLineToBL;

	sf::RenderStates vaTileRS;
	sf::RenderStates BRLineRS;
	sf::RenderStates BLLineRS;

	sf::Transform transform;
	std::string tileTexId = "graphics/V_sheet.png";
	sf::Vector2f tileSize = { 64.f,32.f };
	sf::Texture* texture = nullptr;
	sf::Vector2i tileCnt;
	
	std::unordered_map<int, std::vector<int>> tileTypeMap;

public:
	IsometricTileMap();
	~IsometricTileMap() = default;

	bool SetIsoTile(std::unordered_map<int, std::vector<int>>& tileType, sf::Vector2i count, sf::Vector2f scale);

	void SetIsoLine();

	void SetScale(const sf::Vector2f& scale) override;

	void SetTileCnt(sf::Vector2i tileCnt);
	sf::Vector2i GetTileCnt() { return tileCnt; }

	sf::Vector2f GetIsoTileSize() { return tileSize; }

	void SetLoadedTileType(std::unordered_map<int, std::vector<int>>& tileMap);
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	sf::FloatRect GetTileRect();
};
