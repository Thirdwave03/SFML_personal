#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiHud::SetRotation(float angle)
{
	rotation = angle;
}

void UiHud::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiHud::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiHud::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiHud::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	float textSize = 50.f;
	sf::Font& font = FONT_MGR.Get("fonts/DS-DIGI.ttf");
	mCoordsWorld.setFont(font);
	mCoordsWorld.setCharacterSize(textSize);
	mCoordsWorld.setFillColor(sf::Color::White);
	Utils::SetOrigin(mCoordsWorld, Origins::TL);
	mCoordsUi.setFont(font);
	mCoordsUi.setCharacterSize(textSize);
	mCoordsUi.setFillColor(sf::Color::Yellow);
	Utils::SetOrigin(mCoordsUi, Origins::TL);


}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
}
