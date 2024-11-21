#pragma once
#include "GameObject.h"

class Bug;

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
	
	Types towerType;			//  0 
	std::string textureId;		//  1
	std::string towerName;		//  2
	
	int damage;					//  3
	float attackDuration;		//  4
	float attackTimer;
	float range;				//  5
	sf::CircleShape rangeCircle;
	bool isAreaAttack;			//  6
		
	int price;					//  7
	int priceOnSell;			//  8

	bool isUpgradable;			//  9

	AttackTypes attackType;		// 10
	AttackBonusTypes bonusType;	// 11

	std::wstring description;	// 12
	std::wstring description2;	// 13
	std::wstring description3;	// 14

	int targetNumbers;
	bool isSelected = false;

	Bug* target;

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

	std::wstring GetTowerDescription() { return description; }
	std::wstring GetTowerDescription2() { return description2; }
	std::wstring GetTowerDescription3() { return description3; }

	int GetTowerDamage() { return damage; }
	float GetTowerRange() { return range; }
	int GetTowerPriceOnSell() { return priceOnSell; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire_ElectricRocquet();
	void Fire_SprayF();
	void Fire_SprayR();
	void Fire_MosquitoRepellent();
};
