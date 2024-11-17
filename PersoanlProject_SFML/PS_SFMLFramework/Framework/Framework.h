#pragma once

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	Framework() = default;
	virtual ~Framework() = default;

	Framework(const Framework& other) = delete;
	Framework& operator=(const Framework& other) = delete;

	sf::RenderWindow window;
	sf::ContextSettings settings;

public:
	sf::RenderWindow& GetWindow() { return window; }
	
	sf::Vector2u GetWindowSize() const { return window.getSize(); }
	sf::Vector2f GetWindowSizeF() const { return (sf::Vector2f)window.getSize(); }
	sf::FloatRect GetWindowBounds() const
	{
		auto size = GetWindowSizeF();
		return sf::FloatRect(0.f, 0.f, size.x, size.y);
	}

	virtual void Init(int width, int height, const std::string& name);
	virtual void Do();
	virtual void Release();
};

#define FRAMEWORK (Framework::Instance())