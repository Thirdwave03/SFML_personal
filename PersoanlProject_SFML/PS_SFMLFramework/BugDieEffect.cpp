#include "stdafx.h"
#include "BugDieEffect.h"

BugDieEffect::BugDieEffect(const std::string& name)
	: GameObject(name)
{
	bugEffectSprite.setTexture(TEXTURE_MGR.Get("graphics/enemyOnDie.png"));
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void BugDieEffect::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	bugEffectSprite.setPosition(position);
}

void BugDieEffect::SetRotation(float angle)
{
	rotation = angle;
	bugEffectSprite.setRotation(rotation);
}

void BugDieEffect::SetScale(const sf::Vector2f& s)
{
	scale = s;
	bugEffectSprite.setScale(scale);
}

void BugDieEffect::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(bugEffectSprite, originPreset);
	}
}

void BugDieEffect::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	bugEffectSprite.setOrigin(origin);
}

void BugDieEffect::Init()
{
}

void BugDieEffect::Release()
{
}

void BugDieEffect::Reset()
{
	SetActive(true);
	bugEffectSprite.setColor(sf::Color::White);
	Utils::SetOrigin(bugEffectSprite, Origins::BC);
	bugEffectSprite.setScale(2.f, 2.f);
	timer = 2.5f;
}

void BugDieEffect::Update(float dt)
{
	frequencyTimer += frequency * dt;
	float x = amplitudeX * std::sin(frequencyTimer);
	SetPosition(position + sf::Vector2f(0, speedY * dt));
	bugEffectSprite.setPosition(position + sf::Vector2f{ x, 0 });
	
	sf::Uint8 opacity = (timer * 180)/2.5;
	bugEffectSprite.setColor({ 255, 255, 255, opacity });

	//SetPosition(position + sf::Vector2f{ x, speedY * dt });
	if (timer > 0)
		timer -= dt;
	else
		SetActive(false);
}

void BugDieEffect::Draw(sf::RenderWindow& window)
{
	window.draw(bugEffectSprite);
}
