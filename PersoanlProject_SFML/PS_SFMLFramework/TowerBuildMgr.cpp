#include "stdafx.h"
#include "TowerBuildMgr.h"

TowerBuildMgr::TowerBuildMgr(const std::string& name)
	: GameObject(name)
{


}

void TowerBuildMgr::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void TowerBuildMgr::SetRotation(float angle)
{
	rotation = angle;
}

void TowerBuildMgr::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void TowerBuildMgr::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void TowerBuildMgr::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void TowerBuildMgr::Init()
{
}

void TowerBuildMgr::Release()
{
}

void TowerBuildMgr::Reset()
{
}

void TowerBuildMgr::Update(float dt)
{
	
}

void TowerBuildMgr::Draw(sf::RenderWindow& window)
{
}
