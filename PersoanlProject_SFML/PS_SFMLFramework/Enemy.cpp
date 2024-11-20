#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	originPreset = Origins::BC;
}

void Enemy::SetDestination(sf::Vector2i tile)
{
}

void Enemy::OnHit()
{
}

void Enemy::OnDie()
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
}

void Enemy::SetRotation(float angle)
{
}

void Enemy::SetScale(const sf::Vector2f& scale)
{
}

void Enemy::SetOrigin(Origins preset)
{
}

void Enemy::SetOrigin(const sf::Vector2f& newOrigin)
{
}

void Enemy::Init()
{
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
}

void Enemy::Update(float dt)
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
}
