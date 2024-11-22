#include "stdafx.h"
#include "UiHud.h"
#include "IsometricTileMap.h"
#include "SceneDev1.h"
#include "Towers.h"

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
		/*if (buildingMenu.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
		{
			towerPurchaseGuideBox.setFillColor({ 255, 255, 255, 180 });
			towerPurchaseGuideBox.setOutlineColor(sf::Color::White);
			towerPurchaseGuideText.setFillColor(sf::Color::Black);
		}
		else
		{
			towerPurchaseGuideBox.setFillColor(sf::Color::Transparent);
			towerPurchaseGuideBox.setOutlineColor(sf::Color::Transparent);
			towerPurchaseGuideText.setFillColor(sf::Color::Transparent);
		}*/
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
		SOUND_MGR.PlaySfx("sound/click2.wav");
	}
	if (isBuildBoxOpen && !isBuilding)
	{		
		if (InputMgr::GetKeyDown(sf::Keyboard::Key::Escape) && !escPreventer)
		{
			isBuildBoxOpen = false;
			escPreventer = true;
			SOUND_MGR.PlaySfx("sound/click.mp3");
		}

		if (Utils::Distance(buildBoxCloseButton.getPosition(), (sf::Vector2f)InputMgr::GetMousePosition()) < buildBoxCloseButton.getRadius()
			&& InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
		{
			isBuildBoxOpen = false;
			SOUND_MGR.PlaySfx("sound/click.mp3");
		}

		towerPurchaseGuideBox.setFillColor(sf::Color::Transparent);
		towerPurchaseGuideBox.setOutlineColor(sf::Color::Transparent);
		towerPurchaseGuideText.setFillColor(sf::Color::Transparent);
		if (electricRocquet.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
		{
			towerPurchaseGuideBox.setFillColor({ 255, 255, 255, 180 });
			towerPurchaseGuideBox.setOutlineColor(sf::Color::White);
			towerPurchaseGuideText.setFillColor(sf::Color::Black);
			towerPurchaseGuideText.setPosition({
				towerPurchaseGuideBox.getGlobalBounds().getPosition().x + 25.f,
				towerPurchaseGuideBox.getGlobalBounds().getPosition().y + 
				towerPurchaseGuideBox.getGlobalBounds().getSize().y / 2.f
				});
			towerPurchaseGuideText.setString(TOWER_TABLE->Get(Towers::Types::ElectricRocquet).description
				+ L"\n����Ÿ�� : " + TOWER_TABLE->Get(Towers::Types::ElectricRocquet).description3 + L"\n��Ÿ� : ª��       ���ݷ� : " +
				std::to_wstring(TOWER_TABLE->Get(Towers::Types::ElectricRocquet).damage) +
				L"\n���� : " + std::to_wstring(TOWER_TABLE->Get(Towers::Types::ElectricRocquet).price));
			Utils::SetOrigin(towerPurchaseGuideText, Origins::ML);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
			{
				if(GAME_MGR.GetCoin() >= TOWER_TABLE->Get(Towers::Types::ElectricRocquet).price)
				{
					buildingTower = Towers::Types::ElectricRocquet;
					isBuilding = true;
					clickedTower.setTexture(TEXTURE_MGR.Get("graphics/electricRocquet.png"));
					clickedTower.setScale({ 3.f,3.f });
					clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
					auto a = clickedTower.getColor();
					clickedTower.setColor({ a.r,a.g, a.b, 150 });
					Utils::SetOrigin(clickedTower, Origins::BC);
					SOUND_MGR.PlaySfx("sound/click2.wav");
				}
				else
				{
					SOUND_MGR.PlaySfx("sound/fail.wav");
				}
			}
		}
		if (sprayF.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
		{
			towerPurchaseGuideBox.setFillColor({ 255, 255, 255, 180 });
			towerPurchaseGuideBox.setOutlineColor(sf::Color::White);
			towerPurchaseGuideText.setFillColor(sf::Color::Black);
			towerPurchaseGuideText.setPosition({
				towerPurchaseGuideBox.getGlobalBounds().getPosition().x + 25.f,
				towerPurchaseGuideBox.getGlobalBounds().getPosition().y +
				towerPurchaseGuideBox.getGlobalBounds().getSize().y / 2.f
				});
			towerPurchaseGuideText.setString(TOWER_TABLE->Get(Towers::Types::SprayF).description
				+ L"\n����Ÿ�� : " + TOWER_TABLE->Get(Towers::Types::SprayF).description3 + L"\n��Ÿ� : ����       ���ݷ� : " +
				std::to_wstring(TOWER_TABLE->Get(Towers::Types::SprayF).damage) +
				L"\n���� : " + std::to_wstring(TOWER_TABLE->Get(Towers::Types::SprayF).price));
			Utils::SetOrigin(towerPurchaseGuideText, Origins::ML);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
			{
				if (GAME_MGR.GetCoin() >= TOWER_TABLE->Get(Towers::Types::SprayF).price)
				{
					buildingTower = Towers::Types::SprayF;
					isBuilding = true;
					clickedTower.setTexture(TEXTURE_MGR.Get("graphics/sprayF.png"));
					clickedTower.setScale({ 3.f,3.f });
					clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
					auto a = clickedTower.getColor();
					clickedTower.setColor({ a.r,a.g, a.b, 150 });
					Utils::SetOrigin(clickedTower, Origins::BC);
					SOUND_MGR.PlaySfx("sound/click2.wav");
				}
				else
				{
					SOUND_MGR.PlaySfx("sound/fail.wav");
				}
			}
		}
		if (sprayR.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
		{
			towerPurchaseGuideBox.setFillColor({ 255, 255, 255, 180 });
			towerPurchaseGuideBox.setOutlineColor(sf::Color::White);
			towerPurchaseGuideText.setFillColor(sf::Color::Black);
			towerPurchaseGuideText.setPosition({
				towerPurchaseGuideBox.getGlobalBounds().getPosition().x + 25.f,
				towerPurchaseGuideBox.getGlobalBounds().getPosition().y +
				towerPurchaseGuideBox.getGlobalBounds().getSize().y / 2.f
				});
			towerPurchaseGuideText.setString(TOWER_TABLE->Get(Towers::Types::SprayR).description
				+ L"\n����Ÿ�� : " + TOWER_TABLE->Get(Towers::Types::SprayR).description3 + L"\n��Ÿ� : ����       ���ݷ� : " +
				std::to_wstring(TOWER_TABLE->Get(Towers::Types::SprayR).damage) +
				L"\n���� : " + std::to_wstring(TOWER_TABLE->Get(Towers::Types::SprayR).price));
			Utils::SetOrigin(towerPurchaseGuideText, Origins::ML);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
			{
				if (GAME_MGR.GetCoin() >= TOWER_TABLE->Get(Towers::Types::SprayR).price)
				{
					buildingTower = Towers::Types::SprayR;
					isBuilding = true;
					clickedTower.setTexture(TEXTURE_MGR.Get("graphics/sprayR.png"));
					clickedTower.setScale({ 3.f,3.f });
					clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
					auto a = clickedTower.getColor();
					clickedTower.setColor({ a.r,a.g, a.b, 150 });
					Utils::SetOrigin(clickedTower, Origins::BC);
					SOUND_MGR.PlaySfx("sound/click2.wav");
				}
				else
				{
					SOUND_MGR.PlaySfx("sound/fail.wav");
				}
			}
		}
		if (MosquitoRepellent.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
		{
			towerPurchaseGuideBox.setFillColor({ 255, 255, 255, 180 });
			towerPurchaseGuideBox.setOutlineColor(sf::Color::White);
			towerPurchaseGuideText.setFillColor(sf::Color::Black);
			towerPurchaseGuideText.setPosition({
				towerPurchaseGuideBox.getGlobalBounds().getPosition().x + 25.f,
				towerPurchaseGuideBox.getGlobalBounds().getPosition().y +
				towerPurchaseGuideBox.getGlobalBounds().getSize().y / 2.f
				});
			towerPurchaseGuideText.setString(TOWER_TABLE->Get(Towers::Types::MosquitoRepellent).description
				+ L"\n����Ÿ�� : " + TOWER_TABLE->Get(Towers::Types::MosquitoRepellent).description3 + L"\n��Ÿ� : ���� ª��  ���ݷ� : " +
				std::to_wstring(TOWER_TABLE->Get(Towers::Types::MosquitoRepellent).damage) +
				L"\n���� : " + std::to_wstring(TOWER_TABLE->Get(Towers::Types::MosquitoRepellent).price));
			Utils::SetOrigin(towerPurchaseGuideText, Origins::ML);
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
			{
				if (GAME_MGR.GetCoin() >= TOWER_TABLE->Get(Towers::Types::MosquitoRepellent).price)
				{
					buildingTower = Towers::Types::MosquitoRepellent;
					isBuilding = true;
					clickedTower.setTexture(TEXTURE_MGR.Get("graphics/MosquitoRepellent.png"));
					clickedTower.setScale({ 3.f,3.f });
					clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
					auto a = clickedTower.getColor();
					clickedTower.setColor({ a.r,a.g, a.b, 150 });
					Utils::SetOrigin(clickedTower, Origins::BC);
					SOUND_MGR.PlaySfx("sound/click2.wav");
				}
				else
				{
					SOUND_MGR.PlaySfx("sound/fail.wav");
				}
			}
		}
	}
}

void UiHud::OnBuilding()
{
	clickedTower.setPosition((sf::Vector2f)InputMgr::GetMousePosition());
	Utils::SetOrigin(clickedTower, Origins::BC);
	auto currentTowerPrice = TOWER_TABLE->Get(buildingTower).price;
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left) && !isMouseOnUi)
	{
		if (GAME_MGR.GetCoin() >= currentTowerPrice && VIEW_MGR.GetIsoTileMap().TryBuild())
		{
			GAME_MGR.SpendCoin(currentTowerPrice);
			auto t = (SceneDev1*)SCENE_MGR.GetCurrentScene();
			t->BuildTower();
			isBuilding = false;
			SOUND_MGR.PlaySfx("sound/built.wav");
		}
		else
		{
			// ���� ���� ���
			isBuilding = false;
			SOUND_MGR.PlaySfx("sound/fail.wav");
		}
	}
	if (!escPreventer && (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Right) ||
		InputMgr::GetKeyDown(sf::Keyboard::Key::Escape)))
	{
		isBuilding = false;
		escPreventer = true;
		SOUND_MGR.PlaySfx("sound/click.mp3");
	}
}

bool UiHud::Build()
{
	return false;
}

void UiHud::SetSelectedTower(Towers* tower)
{
	/*if(!isTowerSelected)*/
	selectedTower = tower;	
	isTowerSelected = true;
	isTowerDescriptionOpen = true;
	SOUND_MGR.PlaySfx("sound/click2.wav");
}

void UiHud::SetNullSelectedTower()
{
	selectedTower = nullptr;
	isTowerSelected = false;
	isTowerDescriptionOpen = false;
	SOUND_MGR.PlaySfx("sound/click.mp3");
}

void UiHud::OnTowerSelect()
{
	isTowerSelected = false;
	towerDescriptionPage = 0;
	if (selectedTower == nullptr)
		return;
		
	towerBox.setSize({ 400.f,200.f });

	isTowerDescriptionOpen = true;
}

void UiHud::UpdateTowerDescription()
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Q))
	{
		towerDescriptionPage--;
		SOUND_MGR.PlaySfx("sound/click.mp3");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::E))
	{
		towerDescriptionPage++;
		SOUND_MGR.PlaySfx("sound/click.mp3");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		isTowerDescriptionOpen = false;
		escPreventer = true;
		SOUND_MGR.PlaySfx("sound/click.mp3");
	}
	towerDescriptionPage = Utils::Clamp(towerDescriptionPage, 0, maxPage);

	if (towerDescriptionPage == 0)
	{
		towerDescription.setString(selectedTower->GetTowerDescription());
		towerDescription2.setString(selectedTower->GetTowerDescription2());
		towerDescription3.setString(selectedTower->GetTowerDescription3());
	}
	else if (towerDescriptionPage == 1)
	{
		towerDescription.setString("DAMAGE : " + std::to_string(selectedTower->GetTowerDamage()));
		towerDescription2.setString("RANGE : " + to_string_with_precision(selectedTower->GetTowerRange(),1));
		towerDescription3.setString("SELL AT: " + std::to_string(selectedTower->GetTowerPriceOnSell()));
	}
	else if (towerDescriptionPage == 2)
	{
		towerDescription.setString("!TO BE UPDATED!");
		towerDescription2.setString("!TO BE UPDATED!");
		towerDescription3.setString("!TO BE UPDATED!");
	}
			
	auto towerScreenPos = VIEW_MGR.WorldToScreen(VIEW_MGR.NonModifiedIsoWorldPos(selectedTower->GetIsoTileCoords()));
	auto vSize = VIEW_MGR.GetUiView().getSize();

	towerBox.setPosition((sf::Vector2f)towerScreenPos);


	Origins tempOrigin;
	if (towerScreenPos.x > vSize.x / 2)
	{
		if (towerScreenPos.y > vSize.y / 2)
		{
			tempOrigin = Origins::BR;
		}
		else
		{
			tempOrigin = Origins::TR;
		}
	}
	else
	{
		if (towerScreenPos.y > vSize.y / 2)
		{
			tempOrigin = Origins::BL;
		}
		else
		{
			tempOrigin = Origins::TL;
		}
	}
	Utils::SetOrigin(towerBox, tempOrigin);

	auto a = towerBox.getGlobalBounds();

	towerBoxCloseButton.setPosition({ a.left + a.width - 15.f, a.top + 5.f });
	Utils::SetOrigin(towerBoxCloseButton, Origins::MC);

	towerDescription.setPosition({ a.left + 15.f, a.top + 15.f });
	Utils::SetOrigin(towerDescription, Origins::TL);

	towerDescription2.setPosition({ a.left + 15.f, a.top + 75.f });
	Utils::SetOrigin(towerDescription2, Origins::TL);

	towerDescription3.setPosition({ a.left + 15.f, a.top + 135.f });
	Utils::SetOrigin(towerDescription3, Origins::TL);

	textPageIndicator.setString("<<Q              " +std::to_string(towerDescriptionPage+1) + "/" + std::to_string(maxPage + 1) +  "              E>>");
	textPageIndicator.setPosition({ a.left + a.width / 2.f,a.top + a.height - 20.f });
	Utils::SetOrigin(textPageIndicator, Origins::BC);
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
	isDebugMode = false;
	
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

	towerPurchaseGuideBox.setFillColor({ 255, 255, 255, 180 });
	towerPurchaseGuideBox.setOutlineThickness(10.f);
	towerPurchaseGuideBox.setOutlineColor(sf::Color::White);
	towerPurchaseGuideBox.setPosition(rightX, topY + 380.f);
	towerPurchaseGuideBox.setSize({ 400.f,200.f });
	Utils::SetOrigin(towerPurchaseGuideBox, Origins::TR);

	towerPurchaseGuideText.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	towerPurchaseGuideText.setCharacterSize(30.f);
	towerPurchaseGuideText.setFillColor(sf::Color::Black);

	buildBoxCloseButton.setFillColor(sf::Color::Red);
	buildBoxCloseButton.setRadius(10.f);
	buildBoxCloseButton.setPosition(FRAMEWORK.GetWindowSizeF() / 2.f);
	Utils::SetOrigin(buildBoxCloseButton, Origins::MC);

	towerBox.setFillColor({ 255, 255, 255, 180 });
	towerBox.setOutlineThickness(10.f);
	towerBox.setOutlineColor(sf::Color::White);

	towerBoxCloseButton.setFillColor(sf::Color::Red);
	towerBoxCloseButton.setRadius(10.f);
	towerBoxCloseButton.setPosition(FRAMEWORK.GetWindowSizeF() / 2.f);
	Utils::SetOrigin(towerBoxCloseButton, Origins::MC);

	towerDescription.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	towerDescription.setCharacterSize(30.f);
	towerDescription.setFillColor(sf::Color::Black);

	towerDescription2.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	towerDescription2.setCharacterSize(30.f);
	towerDescription2.setFillColor(sf::Color::Black);

	towerDescription3.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	towerDescription3.setCharacterSize(30.f);
	towerDescription3.setFillColor(sf::Color::Black);

	textPageIndicator.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	textPageIndicator.setCharacterSize(30.f);
	textPageIndicator.setFillColor(sf::Color::Black);

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

	gameoverFadeOut.setFillColor({ 0, 0, 0, 0 });
	gameoverFadeOut.setPosition(FRAMEWORK.GetWindowSizeF()/2.f);
	gameoverFadeOut.setSize({1920.f,1080.f });
	Utils::SetOrigin(gameoverFadeOut, Origins::MC);

	gameoverText.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	gameoverText.setCharacterSize(200.f);
	gameoverText.setFillColor(sf::Color::White);
	gameoverText.setPosition(FRAMEWORK.GetWindowSizeF() / 2.f);
	gameoverText.setString("Game Over.... \n Thank you for playing");
	Utils::SetOrigin(gameoverText, Origins::MC);

	stageInfoButton.setTexture(TEXTURE_MGR.Get("graphics/Info.png"));
	stageInfoButton.setPosition(rightX - 84.f, topY);
	Utils::SetOrigin(stageInfoButton, Origins::TR);

	stageInfoBox.setFillColor({ 255, 255, 255, 180 });
	stageInfoBox.setOutlineThickness(10.f);
	stageInfoBox.setOutlineColor(sf::Color::White);
	stageInfoBox.setPosition(rightX, topY + 380.f);
	stageInfoBox.setSize({ 400.f,200.f });
	Utils::SetOrigin(stageInfoBox, Origins::TR);

	stageInfoBoxCloseButton.setFillColor(sf::Color::Red);
	stageInfoBoxCloseButton.setRadius(10.f);
	stageInfoBoxCloseButton.setPosition(FRAMEWORK.GetWindowSizeF() / 2.f);
	Utils::SetOrigin(stageInfoBoxCloseButton, Origins::MC);

	stageInfo.setFont(FONT_MGR.Get("fonts/koreanFont1.ttf"));
	stageInfo.setCharacterSize(textSize);
	stageInfo.setFillColor(sf::Color::White);
	stageInfo.setPosition(leftX + 80.f, topY);
	Utils::SetOrigin(stageInfo, Origins::TL);
}

void UiHud::ResetDebugObjects()
{
	float textSize = 35.f;
	sf::Font& font = FONT_MGR.Get("fonts/DS-DIGI.ttf");
	mCoordsWorld.setFont(font);
	mCoordsWorld.setCharacterSize(textSize);
	mCoordsWorld.setFillColor(sf::Color::White);
	mCoordsWorld.setPosition({ 50.f, 100.f });
	Utils::SetOrigin(mCoordsWorld, Origins::TL);

	mCoordsScreen.setFont(font);
	mCoordsScreen.setCharacterSize(textSize);
	mCoordsScreen.setFillColor(sf::Color::Yellow);
	mCoordsScreen.setPosition({ 50.f, 250.f });
	Utils::SetOrigin(mCoordsScreen, Origins::TL);

	mCoordsIso.setFont(font);
	mCoordsIso.setCharacterSize(textSize);
	mCoordsIso.setFillColor(sf::Color::Red);
	mCoordsIso.setPosition({ 50.f, 350.f });
	Utils::SetOrigin(mCoordsIso, Origins::TL);

	worldFloat.setFont(font);
	worldFloat.setCharacterSize(textSize);
	worldFloat.setFillColor(sf::Color::Magenta);
	worldFloat.setPosition({ 50.f, 500.f });
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

	if (GAME_MGR.GetLife() <= 0)
	{
		isGameOver = true;
	}


	if (isGameOver)
	{
		if (gameoverFadeOutTimer > 0)
		{
			gameoverFadeOutTimer -= dt;
			gameoverText.setFillColor(sf::Color::Transparent);
		}
		else
		{
			gameoverFadeOutTimer = Utils::Clamp(gameoverFadeOutTimer, 0.f, 5.f);
			gameoverText.setFillColor(sf::Color::White);
		}
		sf::Uint8 temp = 255/4 * (4.f-gameoverFadeOutTimer);
		gameoverFadeOut.setFillColor({ 0,0,0,temp });
		TIME_MGR.SetTimeScale(0.5);
	}
	if (isTowerDescriptionOpen)
	{
		UpdateTowerDescription();
	}
	if (isBuilding)
	{
		OnBuilding();
	}
	if (isTowerSelected)
	{
		OnTowerSelect();
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
	if (isBuildBoxOpen)
	{
		window.draw(buildingMenu);
		window.draw(buildBoxCloseButton);
		window.draw(electricRocquet);
		window.draw(sprayF);
		window.draw(sprayR);
		window.draw(MosquitoRepellent);
		if (isMouseOnUi && !isBuilding)
		{
			window.draw(towerPurchaseGuideBox);
			window.draw(towerPurchaseGuideText);
		}
	}
	if (isBuilding)
	{
		window.draw(clickedTower);
	}
	if (isTowerDescriptionOpen)
	{
		window.draw(towerBox);
		window.draw(towerBoxCloseButton);
		window.draw(towerDescription);
		window.draw(towerDescription2);
		window.draw(towerDescription3);
		window.draw(textPageIndicator);
	}

	window.draw(buildButton);
	window.draw(stageInfoButton);
	window.draw(coinSprite);
	window.draw(coinText);
	window.draw(lifeSprite);
	window.draw(lifeText);
	if (isGameOver)
	{
		window.draw(gameoverFadeOut);
		window.draw(gameoverText);
	}
	if (isDebugMode)
	{
		window.draw(mCoordsWorld);
		window.draw(mCoordsScreen);
		window.draw(mCoordsIso);
		window.draw(worldFloat);
		window.draw(TIME_MGR.GetFrameText());
	}
}
