#pragma once
#include "GameObject.h"

class Bug;

class Towers : public GameObject
{
public:
	enum class Types
	{
		None = -1,
		ElectricRocquet,				//  0
		SprayF,							//  1
		SprayR,							//  2
		MosquitoRepellent,				//  3
		ElectricRocquetS,				//  4
		UVRepellent,					//  5
		ElectricRocquetU,				//  6
		Lightning,						//  7
		TeslaCoil,						//  8
		SprayFS,						//  9
		SprayFreeze,					// 10
		Ice,							// 11
		SprayTorch,						// 12
		Fire,							// 13
		HomeMat,						// 14
		HomeMatS,						// 15
	};

	enum class AttackTypes
	{
		Both,
		Ground,
		Air,
	};



protected:
	sf::Sprite towerSprite;
	sf::Sprite sprayStraw;
	sf::Sprite elecRocquetEffect;
	sf::VertexArray fireEffects;
	sf::Sprite electricEffectOnEnemy;
	sf::Sprite lighteningEffectOnEnemy;
	sf::Sprite mosquitoRepellentEffect;
	sf::Sprite UVRepellentEffect;
	sf::Sprite homeMatEffect;
	sf::Sprite teslaCoilEffect;
	sf::Sprite iceEffectOnEnemy;
	sf::Sprite fireEffect;
	
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

	int upgradableTowers;		//  9

	AttackTypes attackType;		// 10
	
	float slow;				  	// 11
	float stun;				  	// 12

	std::wstring description; 	// 13
	std::wstring description2;	// 14
	std::wstring description3;	// 15

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
	int GetPrice() { return price; }
	float GetTowerAttackDuration() { return attackDuration; }
	int GetTowerUpgradables() { return upgradableTowers; }
	Types GetTowerType() { return towerType; }
	std::string GetTextureId() { return textureId; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateSprayStraw(float dt);
	void UpdateSprayEffect(float dt);
	void UpdateSprayEffectR(float dt);
	void UpdateElecRocquetEffect(float dt);
	void UpdateLighteningEffect(float dt);
	void UpdateIceEffect(float dt);
	void UpdateFireEffect(float dt);
	void UpdateMosquitoRepellentEffect(float dt);
	void UpdateUVRepellentEffect(float dt);
	void UpdateHomeMatEffect(float dt);
	void UpdateTeslaCoilEffect(float dt);
	void Draw(sf::RenderWindow& window) override;


	void Fire_ElectricRocquet();
	void Fire_Lightening();
	void Fire_Ice();
	void Fire_Fire();
	void Fire_Spray();
	void Fire_SprayR();
	void Fire_AreaAttack();

	void SprayEffect();
	void SprayEffectR();
	void ElectricEffectOnEnemy();
	void LighteiningEffectOnEnemy();
	void IceEffectOnEnemy();
	void FireEffectOnEnemy();
};
