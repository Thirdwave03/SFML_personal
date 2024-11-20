#pragma once

class Enemy : public GameObject
{	
	enum class BugTypes
	{
		Cockroach,
		Spider,
		Mosquito,
		Fly,
	};
	
protected:
	float hp;
	float speed;
	int gold;

	sf::Vector2f direction;
	sf::Vector2i destinationTile;
	sf::FloatRect hpBar;
	sf::FloatRect maxhpBar;
	
	std::string description;

	float timerSlow;
	bool isSlowed;

	float timerStun;
	bool isStunned;	

public:
	Enemy(const std::string& name = "");
	~Enemy() = default;

	void SetDestination(sf::Vector2i tile);
	void OnHit();
	void OnDie();

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
