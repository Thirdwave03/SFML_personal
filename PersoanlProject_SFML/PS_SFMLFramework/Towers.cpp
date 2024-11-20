#include "stdafx.h"
#include "Towers.h"
#include "Enemy.h"

Towers::Towers(const std::string& name)
	:GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	originPreset = Origins::BC;
}

void Towers::Set()
{
}

void Towers::OnSell()
{
}

void Towers::OnConsturction()
{

}

void Towers::SetType(TowerTypes type)
{
	switch ((int)type)
	{
	case 0:
		towerSprite.setTexture(TEXTURE_MGR.Get("graphics/electricRocquet.png"),true);

		break;
	case 1:
		towerSprite.setTexture(TEXTURE_MGR.Get("graphics/SprayF.png"), true);

		break;
	case 2:
		towerSprite.setTexture(TEXTURE_MGR.Get("graphics/SprayR.png"), true);

		break;
	case 3:
		towerSprite.setTexture(TEXTURE_MGR.Get("graphics/mosquitoRepellent.png"), true);

		break;
	}
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetScale({ 3.f,3.f });
	SetOrigin(Origins::BC);
}

void Towers::Fire()
{
}

void Towers::SetTarget()
{
}

void Towers::SetIsoTileCoords(sf::Vector2i isoCoord)
{
	isoTileCoords = isoCoord;
	SetPosition({ VIEW_MGR.NonModifiedIsoWorldPos(isoTileCoords).x, VIEW_MGR.NonModifiedIsoWorldPos(isoTileCoords).y + 20.f });
}

void Towers::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	towerSprite.setPosition(position);
}

void Towers::SetRotation(float angle)
{
}

void Towers::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	towerSprite.setScale(scale);
	
}

void Towers::SetOrigin(Origins preset)
{
	this->originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(towerSprite, originPreset);
	}
}

void Towers::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	towerSprite.setOrigin(newOrigin);
}

void Towers::Init()
{
}

void Towers::Release()
{
}

void Towers::Reset()
{
}

void Towers::Update(float dt)
{
	//SetOrigin(originPreset);
}

void Towers::Draw(sf::RenderWindow& window)
{
	window.draw(towerSprite);
}
