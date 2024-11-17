#pragma once
#include "GameObject.h"

class IsometricTile : public GameObject
{
protected:
	sf::VertexArray vaTile;
	sf::VertexArray vaLineToBR;
	sf::VertexArray vaLineToBL;
	sf::Transform transform;
	std::string tileTexId = "graphics/V_sheet.png";
	sf::Vector2f tileSize = { 64.f,64.f };
	sf::Texture* texture = nullptr;
	sf::Vector2i tileCnt;

public:
	IsometricTile();
	~IsometricTile() = default;

	bool SetIsoTile(const int* tileType, sf::Vector2i count);

	void SetIsoLine();
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
