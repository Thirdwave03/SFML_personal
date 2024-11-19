#pragma once

class Enemy : public GameObject
{
protected:
	float hp;
	float speed;
	sf::Vector2f direction;
	sf::Vector2i destinationTile;
	sf::FloatRect hpBar;
	sf::FloatRect maxhpBar;
	
	float timerSlow;
	bool isSlowed;

	float timerStun;
	bool isStunned;	

public:
	Enemy(const std::string& name = "");
	~Enemy() = default;

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
