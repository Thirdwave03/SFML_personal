#pragma once

class BugDieEffect : public GameObject
{
protected:
	sf::Sprite bugEffectSprite;
	float amplitudeX = 20;
	float frequency = 4.f;
	float frequencyTimer = 0.f;
	float speedY = -50;

	float timer = 2.5f;


public:
	BugDieEffect(const std::string& name = "");
	~BugDieEffect() = default;

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
