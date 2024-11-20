#include "stdafx.h"
#include "Bug.h"

Bug::Bug(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	originPreset = Origins::BC;
	SetScale({ 3.f,3.f });
	SetOrigin(originPreset);
}

void Bug::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bug::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bug::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bug::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void Bug::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bug::Init()
{
	Reset();
}

void Bug::Release()
{

}

void Bug::Reset()
{
	SetActive(true);
	speedMultiplier = 1.f;

	//for test only
	body.setTexture(TEXTURE_MGR.Get(textureId));
	maxHp = 20;
	hp = maxHp;
	speed = 300;
	gold = 2;
	deadTimer = 3.f;

	accumTime = 0;
	animationDuration = 0.3;
}

void Bug::Update(float dt)
{
	if (!isDead)
	{
		UpdateAnimation(dt);
		UpdateDirection(dt);
		SetPosition(position + direction * speed * speedMultiplier * dt);
	}
	
	if (hp <= 0)
	{
		isDead = true;
	}

	if (isDead)
	{
		animationTarget = { 0, 128, 64, 64 };
		body.setTextureRect(animationTarget);
		deadTimer -= dt;
	}

	if (deadTimer < 0 && isDead)
	{
		SetActive(false);
	}
}

void Bug::UpdateDirection(float dt)
{
	direction = Utils::GetNormal(VIEW_MGR.IsoToWorld(destinationTile) - position);
}

void Bug::UpdateAnimation(float dt)
{	
	accumTime += dt * speedMultiplier;
	if (accumTime > animationDuration)
	{
		accumTime -= animationDuration;
		animationFlagH = !animationFlagH;
	}	
	if (direction.y < 0)
	{
		animationFlagV = true;
	}
	else
	{
		animationFlagV = false;
	}

	animationTarget = { 64 * animationFlagH, 64 * animationFlagV, 64,  64 };
	body.setTextureRect(animationTarget);


	// test
	tempTimer -= dt;
	if (tempTimer < 0)
		isDead = true;
}

void Bug::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
