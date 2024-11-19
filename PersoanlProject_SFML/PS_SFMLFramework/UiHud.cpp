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
	mCoordsScreen.setPosition({ 50.f, 200.f });
	Utils::SetOrigin(mCoordsScreen, Origins::TL);

	mCoordsIso.setFont(font);
	mCoordsIso.setCharacterSize(textSize);
	mCoordsIso.setFillColor(sf::Color::Red);
	mCoordsIso.setPosition({ 50.f, 300.f });
	Utils::SetOrigin(mCoordsIso, Origins::TL);

	worldFloat.setFont(font);
	worldFloat.setCharacterSize(textSize);
	worldFloat.setFillColor(sf::Color::Magenta);
	worldFloat.setPosition({ 50.f, 450.f });
	Utils::SetOrigin(worldFloat, Origins::TL);
}

void UiHud::Update(float dt)
{
	auto tempX = (int)VIEW_MGR.GetWorldMousePos().x;
	while (tempX >= 128)
		tempX -= 128;
	auto tempY = (int)VIEW_MGR.GetScreenMousePos().y;
	while (tempY >= 64)
		tempY -= 64;

	mCoordsWorld.setString(
		"Worlds X : " + std::to_string((int)VIEW_MGR.GetWorldMousePos().x)
		+ "\nWorlds Y : " + std::to_string((int)VIEW_MGR.GetWorldMousePos().y)
		+ "\nTile X : " + std::to_string(tempX)
		+ "\nTile Y : " + std::to_string(tempY)
		);
	Utils::SetOrigin(mCoordsWorld, Origins::TL);
	mCoordsScreen.setString(
		"Screen X : " + std::to_string(VIEW_MGR.GetScreenMousePos().x)
		+ "\nScreen Y : " + std::to_string(VIEW_MGR.GetScreenMousePos().y)
		);
	Utils::SetOrigin(mCoordsScreen, Origins::TL);

	mCoordsIso.setString(
		"Iso X : " + std::to_string(VIEW_MGR.GetIsoMousePos().x)
		+ "\nIso Y : " + std::to_string(VIEW_MGR.GetIsoMousePos().y)
		+ "\nIsoToWorld X : " + std::to_string(VIEW_MGR.IsoToWorldTest().x)
		+ "\nIsoToWorld Y : " + std::to_string(VIEW_MGR.IsoToWorldTest().y)
		);
	Utils::SetOrigin(mCoordsIso, Origins::TL);

	// for World Float Check only

	//auto tempBL = VIEW_MGR.GetWorldMousePosFloatBL() + 32.f;
	//while (tempBL >= 64.f)
	//	tempBL -= 64.f;

	//auto tempBR = VIEW_MGR.GetWorldMousePosFloatBR() + 32.f;
	//while (tempBR >= 64.f)
	//	tempBR -= 64.f;
	//while (tempBR < 0)
	//	tempBR += 64.f;

	worldFloat.setString(
		"WorldFloat(BL) : " + std::to_string(VIEW_MGR.GetWorldMousePosFloatBL())
		+ "\nTileFloat(BL) : " + std::to_string(VIEW_MGR.GetDevidedBL())
		+ "\nWorldFloat(BR) : " + std::to_string(VIEW_MGR.GetWorldMousePosFloatBR())
		+ "\nTileFloat(BR) : " + std::to_string(VIEW_MGR.GetDevidedBR())
		+ "\nX index : " + std::to_string(VIEW_MGR.GetXindex())
		+ "\nY index : " + std::to_string(VIEW_MGR.GetYindex())
		);
	Utils::SetOrigin(worldFloat, Origins::TL);
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(mCoordsWorld);
	window.draw(mCoordsScreen);
	window.draw(mCoordsIso);
	window.draw(worldFloat);
}
