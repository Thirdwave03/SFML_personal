#include "stdafx.h"
#include "UiHud.h"
#include "IsometricTileMap.h"
#include "SceneDev1.h"

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

void UiHud::TurnDebugMode()
{
	isDebugMode = !isDebugMode;
}


/// <summary>
/// BuildBoxOpen += 4, Mouse On Ui += 2, isBuilding += 1
/// </summary>
/// <returns></returns>
int UiHud::GetBoolStatus()
{
	int statusInt = 0;
	if (isBuildBoxOpen)
		statusInt += 4;
	if (isMouseOnUi)
		statusInt += 2;
	if (isBuilding)
		statusInt += 1;
	return statusInt;
}

void UiHud::UiMouseCheck()
{
	if (buildButton.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition())||
		buildingMenu.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
	{
		isMouseOnUi = true;
	}
	else
	{
		isMouseOnUi = false;
	}
	if (buildButton.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		buildingMenu.setSize({600.f,250.f});
		Utils::SetOrigin(buildingMenu, Origins::TR);
		auto a = buildingMenu.getGlobalBounds();
		buildBoxCloseButton.setPosition({ a.left + a.width - 15.f, a.top + 5.f });
		
		electricRocquet.setPosition({ a.left + 80, a.top + a.height - 100 });
		electricRocquet.setScale(buildingIconScale);
		Utils::SetOrigin(electricRocquet, Origins::BC);
		sprayF.setPosition({ a.left + 200, a.top + a.height - 100 });
		sprayF.setScale(buildingIconScale);
		Utils::SetOrigin(sprayF, Origins::BC);
		sprayR.setPosition({ a.left + 320, a.top + a.height - 100 });
		sprayR.setScale(buildingIconScale);
		Utils::SetOrigin(sprayR, Origins::BC);
		MosquitoRepellent.setPosition({ a.left + 440, a.top + a.height - 100 });
		MosquitoRepellent.setScale(buildingIconScale);
		Utils::SetOrigin(MosquitoRepellent, Origins::BC);

		isBuildBoxOpen = true;
	}
	if (isBuildBoxOpen && !isBuilding)
	{		
		if (InputMgr::GetKeyDown(sf::Keyboard::Key::Escape) && !escPreventer)
		{
			isBuildBoxOpen = false;
			escPreventer = true;
		}


		if (Utils::Distance(buildBoxCloseButton.getPosition(), (sf::Vector2f)InputMgr::GetMousePosition()) < buildBoxCloseButton.getRadius()
			&& InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			isBuildBoxOpen = false;
		}

		if (electricRocquet.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			buildingTower = TowerTypes::ElectricRocquet;
			isBuilding = true;
			clickedTower.setTexture(TEXTURE_MGR.Get("graphics/electricRocquet.png"));
			clickedTower.setScale({ 3.f,3.f });
			clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
			auto a = clickedTower.getColor();
			clickedTower.setColor({a.r,a.g, a.b, 150});
			Utils::SetOrigin(clickedTower, Origins::BC);
		}
		if (sprayF.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			buildingTower = TowerTypes::SprayF;
			isBuilding = true;
			clickedTower.setTexture(TEXTURE_MGR.Get("graphics/sprayF.png"));
			clickedTower.setScale({ 3.f,3.f });
			clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
			auto a = clickedTower.getColor();
			clickedTower.setColor({ a.r,a.g, a.b, 150 });
			Utils::SetOrigin(clickedTower, Origins::BC);
		}
		if (sprayR.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			buildingTower = TowerTypes::SprayR;
			isBuilding = true;
			clickedTower.setTexture(TEXTURE_MGR.Get("graphics/sprayR.png"));
			clickedTower.setScale({ 3.f,3.f });
			clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
			auto a = clickedTower.getColor();
			clickedTower.setColor({ a.r,a.g, a.b, 150 });
			Utils::SetOrigin(clickedTower, Origins::BC);
		}
		if (MosquitoRepellent.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			buildingTower = TowerTypes::MosquitoRepellent;
			isBuilding = true;
			clickedTower.setTexture(TEXTURE_MGR.Get("graphics/MosquitoRepellent.png"));
			clickedTower.setScale({ 3.f,3.f });
			clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
			auto a = clickedTower.getColor();
			clickedTower.setColor({ a.r,a.g, a.b, 150 });
			Utils::SetOrigin(clickedTower, Origins::BC);
		}
	}
}

void UiHud::OnBuilding()
{
	clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
	Utils::SetOrigin(clickedTower, Origins::BC);
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		if (VIEW_MGR.GetIsoTileMap().TryBuild())
		{
			auto t = (SceneDev1*)SCENE_MGR.GetCurrentScene();
			t->BuildTower();
			isBuilding = false;
		}
		else
		{
			// 실패 사운드 재생
			isBuilding = false;
		}
	}
	if (!escPreventer && (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Right) ||
		InputMgr::GetKeyDown(sf::Keyboard::Key::Escape)))
	{
		isBuilding = false;
		escPreventer = true;
	}
}

bool UiHud::Build()
{
	return false;
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
	ResetDebugObjects();
	
	float textSize = 50.f;
	auto uiViewSize = VIEW_MGR.GetUiView().getSize();
	float leftX = 25.f;
	float topY = 25.f;
	float rightX = uiViewSize.x - 25.f;
	float bottomY = uiViewSize.y - 75.f;
	
	buildButton.setTexture(TEXTURE_MGR.Get("graphics/Build.png"));
	buildButton.setPosition(rightX, topY);
	Utils::SetOrigin(buildButton, Origins::TR);

	buildingMenu.setFillColor({ 255, 255, 255, 180 });
	buildingMenu.setOutlineThickness(10.f);
	buildingMenu.setOutlineColor(sf::Color::White);
	buildingMenu.setPosition(rightX, topY + 100.f);
	Utils::SetOrigin(buildingMenu, Origins::TR);

	buildBoxCloseButton.setFillColor(sf::Color::Red);
	buildBoxCloseButton.setRadius(10.f);
	buildBoxCloseButton.setPosition(FRAMEWORK.GetWindowSizeF() / 2.f);
	Utils::SetOrigin(buildBoxCloseButton, Origins::MC);

	electricRocquet.setTexture(TEXTURE_MGR.Get("graphics/electricRocquet.png"));
	electricRocquet.setScale(buildingIconScale);
	Utils::SetOrigin(electricRocquet, Origins::BC);

	sprayF.setTexture(TEXTURE_MGR.Get("graphics/sprayF.png"));
	sprayF.setScale(buildingIconScale);
	Utils::SetOrigin(sprayF, Origins::BC);

	sprayR.setTexture(TEXTURE_MGR.Get("graphics/sprayR.png"));
	sprayR.setScale(buildingIconScale);
	Utils::SetOrigin(sprayR, Origins::BC);

	MosquitoRepellent.setTexture(TEXTURE_MGR.Get("graphics/MosquitoRepellent.png"));
	MosquitoRepellent.setScale(buildingIconScale);
	Utils::SetOrigin(MosquitoRepellent, Origins::BC);


	
	coinSprite.setTexture(TEXTURE_MGR.Get("graphics/Coin.png"));
	coinSprite.setPosition(leftX, topY);
	Utils::SetOrigin(coinSprite, Origins::TL);
		
	coinSprite.setTexture(TEXTURE_MGR.Get("graphics/Coin.png"));
	coinSprite.setPosition(leftX, topY);
	Utils::SetOrigin(coinSprite, Origins::TL);

	coinText.setFont(FONT_MGR.Get("fonts/blackwood_castle.ttf"));
	coinText.setCharacterSize(textSize);
	coinText.setFillColor(sf::Color::White);
	coinText.setPosition(leftX + 80.f, topY);
	Utils::SetOrigin(coinText, Origins::TL);

	lifeSprite.setTexture(TEXTURE_MGR.Get("graphics/pixelHeart.png"));
	lifeSprite.setPosition(leftX, bottomY);
	Utils::SetOrigin(lifeSprite, Origins::TL);

	lifeText.setFont(FONT_MGR.Get("fonts/blackwood_castle.ttf"));
	lifeText.setCharacterSize(textSize);
	lifeText.setFillColor(sf::Color::White);
	lifeText.setPosition(leftX + 80.f, bottomY);
	Utils::SetOrigin(lifeText, Origins::TL);
}

void UiHud::ResetDebugObjects()
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
	escPreventer = false;
	if (isDebugMode)
		UpdateDebugObjects(dt);

	coinText.setString(std::to_string(GAME_MGR.GetCoin()));
	Utils::SetOrigin(coinText, Origins::TL);

	lifeText.setString(std::to_string(GAME_MGR.GetLife()));
	Utils::SetOrigin(lifeText, Origins::TL);

	if (isBuilding)
	{
		OnBuilding();
	}
}

void UiHud::FixedUpdate(float dt)
{
	auto mPos = VIEW_MGR.GetScreenMousePos();
	if (mPos.x > 1700.f && mPos.y < 200.f)
	{

	}
	UiMouseCheck();
}

void UiHud::UpdateDebugObjects(float dt)
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
	if (isDebugMode)
	{
		window.draw(mCoordsWorld);
		window.draw(mCoordsScreen);
		window.draw(mCoordsIso);
		window.draw(worldFloat);
	}
	if (isBuildBoxOpen)
	{
		window.draw(buildingMenu);
		window.draw(buildBoxCloseButton);
		window.draw(electricRocquet);
		window.draw(sprayF);
		window.draw(sprayR);
		window.draw(MosquitoRepellent);
	}
	if (isBuilding)
	{
		window.draw(clickedTower);
	}

	window.draw(buildButton);
	window.draw(coinSprite);
	window.draw(coinText);
	window.draw(lifeSprite);
	window.draw(lifeText);
}
