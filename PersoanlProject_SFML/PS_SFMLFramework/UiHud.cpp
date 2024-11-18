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
	float textSize = 35.f;
	sf::Font& font = FONT_MGR.Get("fonts/DS-DIGI.ttf");
	mCoordsWorld.setFont(font);
	mCoordsWorld.setCharacterSize(textSize);
	mCoordsWorld.setFillColor(sf::Color::White);
	mCoordsWorld.setPosition({ 50.f, 50.f });
	Utils::SetOrigin(mCoordsWorld, Origins::TL);

	mCoordsScreen.setFont(font);
	mCoordsScreen.setCharacterSize(textSize);
	mCoordsScreen.setFillColor(sf::Color::Yellow);
	mCoordsScreen.setPosition({ 50.f, 150.f });
	Utils::SetOrigin(mCoordsScreen, Origins::TL);

	mCoordsIso.setFont(font);
	mCoordsIso.setCharacterSize(textSize);
	mCoordsIso.setFillColor(sf::Color::Red);
	mCoordsIso.setPosition({ 50.f, 250.f });
	Utils::SetOrigin(mCoordsIso, Origins::TL);

	worldFloat.setFont(font);
	worldFloat.setCharacterSize(textSize);
	worldFloat.setFillColor(sf::Color::Magenta);
	worldFloat.setPosition({ 50.f, 350.f });
	Utils::SetOrigin(worldFloat, Origins::TL);
}

void UiHud::Update(float dt)
{
	mCoordsWorld.setString(
		"Worlds X : " + std::to_string(VIEW_MGR.GetWorldMousePos().x)
		+ "\nWorlds Y : " + std::to_string(VIEW_MGR.GetWorldMousePos().y));
	Utils::SetOrigin(mCoordsWorld, Origins::TL);
	mCoordsScreen.setString(
		"Screen X : " + std::to_string(VIEW_MGR.GetScreenMousePos().x)
		+ "\nScreen Y : " + std::to_string(VIEW_MGR.GetScreenMousePos().y));
	Utils::SetOrigin(mCoordsScreen, Origins::TL);

	mCoordsIso.setString(
		"Iso X : " + std::to_string(VIEW_MGR.GetIsoMousePos().x)
		+ "\nIso Y : " + std::to_string(VIEW_MGR.GetIsoMousePos().y));
	Utils::SetOrigin(mCoordsIso, Origins::TL);

	// for World Float Check only

	auto tempFloat = VIEW_MGR.GetWorldMousePosFloat() + 32.f;
	while (tempFloat >= 64.f)
		tempFloat -= 64.f;

	worldFloat.setString(
		"WorldFloat : " + std::to_string(VIEW_MGR.GetWorldMousePosFloat())
		+ "\nTileFloat : " + std::to_string(tempFloat));
	Utils::SetOrigin(worldFloat, Origins::TL);
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(mCoordsWorld);
	window.draw(mCoordsScreen);
	window.draw(mCoordsIso);
	window.draw(worldFloat);
}
