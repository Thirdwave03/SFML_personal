#pragma once
#include "GameObject.h"

class Enemy;

class Towers : public GameObject
{
public:
	enum class Types
	{
		None = -1,
		ElectricRocquet,
		SprayF,
		SprayR,
		MosquitoRepellent,
	};

	enum class AttackTypes
	{
		Both,
		Ground,
		Air,
	};

	enum class AttackBonusTypes
	{
		Default,
		CockroachBonus,
		MosquitoBonus,
		SpiderBonus,
		FlyBonus,
	};



protected:
	sf::Sprite towerSprite;

	float damage;
	float attackDuration;
	int price;

	float range;
	sf::CircleShape rangeCircle;

	bool isAreaAttack;
	int targetNumbers;

	bool isConstructable;
	bool isUpgradable;
	bool isSelected = false;

	Types towerType;

	AttackTypes attackType;

	std::string description;

	std::vector<Enemy*> target;

	sf::Vector2i isoTileCoords = { 0,0 };

public:
	Towers(const std::string& name = "");
	~Towers() = default;

	virtual void Set();
	virtual void OnSell();
	virtual void OnConsturction();
	void SetType(Types type);
	void Fire();
	void SetTarget();

	void SetIsoTileCoords(sf::Vector2i isoCoord);
	sf::Vector2i GetIsoTileCoords() { return isoTileCoords; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetRangeCircle();

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetSelected(bool selected) { isSelected = selected; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
