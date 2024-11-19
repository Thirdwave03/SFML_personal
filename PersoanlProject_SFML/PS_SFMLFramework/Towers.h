#pragma once
#include "GameObject.h"
class Towers : public GameObject
{
protected:
	float damage;
	float attackDuration;
	float range;
	int price;

	bool isConstructable;
	bool isUpgradable;

	std::string description;

public:
	Towers(const std::string& name = "");
	~Towers() = default;

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
