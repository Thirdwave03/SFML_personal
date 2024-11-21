#pragma once

class Bug : public GameObject
{	
public:
	enum class BugType
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
	float maxHp;
	float hp;
	float speed;
	float speedMultiplier = 1.f;
	int gold;

	sf::Sprite body;	
	sf::IntRect animationTarget;

	std::string textureId = "graphics/Cockroach_Sheet.png";

	BugType bugType;
	BugLayerType layerType;

	float animationDuration;
	float accumTime;
	bool animationFlagH = false;
	bool animationFlagV = false;

	sf::Vector2f direction;
	sf::Vector2i destinationTile;
	sf::RectangleShape hpBar;
	sf::RectangleShape maxhpBar;
	
	std::string description;

	float timerSlow;
	bool isSlowed;

	float timerStun;
	bool isStunned;

	bool isDead = false;
	float deadTimer = 3.f;

	float tempTimer = 5.f;

	int waypointIndex = 1;

public:
	Bug(const std::string& name = "Bug");
	~Bug() = default;

	void SetDestination(sf::Vector2i tile);
	void OnHit();
	void OnDie();

	BugType GetBugType() { return bugType; }
	BugLayerType GetBugLayerType() { return layerType; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetDestinationTile(sf::Vector2i destination) { destinationTile = destination; }

	void OnArrival();

	bool GetActive();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateDirection(float dt);
	void UpdateAnimation(float dt);
	void UpdateHealthBar(float dt);
	void Draw(sf::RenderWindow& window) override;
};
