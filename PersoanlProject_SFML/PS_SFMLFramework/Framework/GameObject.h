#pragma once

class GameObject
{
private:
	sf::RectangleShape temp;

protected:
	std::string name;

	bool active = true;

	sf::Vector2f position;
	float rotation = 0.f;
	sf::Vector2f scale = { 1,1 };

	Origins originPreset;
	sf::Vector2f origin;

public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	float GetRotation() const { return rotation; }
	virtual void SetRotation(float angle) { rotation = angle; }
	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& scale) { this->scale = scale; }

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	virtual sf::FloatRect GetLocalBounds() { return { 0.f,0.f,0.f,0.f }; }
	virtual sf::FloatRect GetGlobalBounds() { return { 0.f,0.f,0.f,0.f }; }

	virtual sf::RectangleShape& GetDebugBox() { return temp; }

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Reset() = 0;

	virtual void FixedUpdate(float dt) {}
	virtual void Update(float dt) = 0;
	virtual void LateUpdate(float dt) {}
	virtual void Draw(sf::RenderWindow& window) = 0;

	virtual void TurnDebugBox(bool active, sf::Color color = sf::Color::Red) {}

	bool operator>(const GameObject& other) {
		if (this->sortingLayer != other.sortingLayer)
			return this->sortingLayer > other.sortingLayer;
		return this->sortingOrder > other.sortingOrder;
	}
};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b) const
	{
		if (a->sortingLayer != b->sortingLayer)
			return a->sortingLayer > b->sortingLayer;
		if (a->sortingOrder != b->sortingOrder)
			return a->sortingOrder > b->sortingOrder;
		return a->GetPosition().y > b->GetPosition().y;
	}
};

