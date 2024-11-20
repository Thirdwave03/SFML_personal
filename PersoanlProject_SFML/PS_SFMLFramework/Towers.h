#pragma once
#include "GameObject.h"

class Enemy;

class Towers : public GameObject
{
	enum class AttackBonusTypes
	{
		Default,
		CockroachBonus,
		MosquitoBonus,
		SpiderBonus,
		FlyBonus,
	};

	enum class AttackTypes
	{
		Almighty,
		GroundOnly,
		AirOnly,
	};

protected:
	sf::Sprite towerSprite;

	float damage;
	float attackDuration;
	int price;

	float range;
	sf::CircleShape rangeCircle;

	bool isConstructable;
	bool isUpgradable;

	std::string description;

	std::vector<Enemy*> target;

	sf::Vector2i isoTileCoords = { 0,0 };

	int targetNumbers;

public:
	Towers(const std::string& name = "");
	~Towers() = default;

	virtual void Set();
	virtual void OnSell();
	virtual void OnConsturction();
	void SetType(TowerTypes type);
	void Fire();
	void SetTarget();

	void SetIsoTileCoords(sf::Vector2i isoCoord);
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
