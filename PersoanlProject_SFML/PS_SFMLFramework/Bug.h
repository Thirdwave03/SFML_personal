#pragma once

class Bug : public GameObject
{	
public:
	enum class BugTypes
	{
		Cockroach,
		Spider,
		Mosquito,
		Fly,
	};

	enum class BugLayerType
	{
		Ground,
		Air,
	};
	
protected:
	Bug::BugTypes bugType;					//  0
	std::string textureId;					//  1
	std::string bugName;					//  2

	int maxHp;								//  3
	int hp;
	float speed;							//  4
	float speedMultiplier;
	int damage;								//  5
	int gold;								//  6
	float animationDuration;				//  7
	Bug::BugLayerType layerType;			//  8

	std::wstring description;				//  9
	std::wstring description2;				// 10
	std::wstring description3;				// 11

	sf::Sprite bugSprite;
	sf::IntRect animationTarget;
	sf::Sprite stunSprite;
	sf::IntRect stunAnimationTarget;

	float accumTime;
	bool stunAnimationFlag = false;

	bool animationFlagH = false;
	bool animationFlagV = false;

	sf::Vector2f direction;
	sf::Vector2i destinationTile;
	sf::RectangleShape hpBar;
	sf::RectangleShape maxhpBar;

	float timerSlow = 0;
	float slowMultiplier = 1.f;

	float timerStun;
	float stunAccumTime =0.5f;
	bool isStunned;

	bool isGoldRewarded = false;
	bool isDead = false;
	float deadTimer = 3.f;

	float onHitTimer = 0.f;	

	int waypointIndex = 1;

public:
	Bug(const std::string& name = "Bug");
	~Bug() = default;

	BugTypes GetBugType() { return bugType; }
	BugLayerType GetBugLayerType() { return layerType; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetDestinationTile(sf::Vector2i destination) { destinationTile = destination; }

	void SetSlowTimer(float slow);
	void SetStunTimer(float stun);
	float GetSlowTimer() { return timerSlow; }
	float GetStunTimer() { return timerStun; }

	void OnDamage(int damage);
	void OnDie();

	int GetHp() { return hp; }

	void SetType(int bugTypeId);

	void OnArrival();

	bool GetActive();


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateDirection(float dt);
	void UpdateAnimation(float dt);
	void UpdateStunAnimation(float dt);
	void UpdateHealthBar(float dt);
	void Draw(sf::RenderWindow& window) override;
};
