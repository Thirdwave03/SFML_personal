#include "stdafx.h"
#include "SceneDev1.h"
#include "UiHud.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
    auto text = AddGo(new TextGo("fonts/DS-DIGI.ttf", "Scene Name"));
    isoTile = AddGo(new IsometricTileMap());    

    //const int tileType[] =
    //{
    //    0, 1, 
    //    2, 0,
    //};


    isoTile->SetIsoTile(TILE_TABLE->GetTileMapTable(), TILE_TABLE->GetTileMapCount(), { 3.f,3.f });
    isoTile->SetIsoLine();
    isoTile->GetScale();
    isoTile->GetIsoTileSize();
    VIEW_MGR.SetViewBoundary(isoTile->GetTileRect(), isoTile->GetIsoTileSize(), isoTile->GetScale());
    //isoTile->SetIsoTileTest();

    text->sortingLayer = SortingLayers::UI;
    text->Set(25, sf::Color::White);
    text->SetString("Dev 1");

    uiHud = AddGo(new UiHud("UiHud"));
    Scene::Init();
}

void SceneDev1::Enter()
{
    //worldView.setSize(FRAMEWORK.GetWindowSizeF()/2.f);
    VIEW_MGR.GetWorldView() = FRAMEWORK.GetWindow().getDefaultView();

   
    Scene::Enter();

    VIEW_MGR.GetWorldView().setCenter(FRAMEWORK.GetWindowSizeF() / 2.f);
}

void SceneDev1::Exit()
{
    Scene::Exit();
}

void SceneDev1::Update(float dt)
{
    Scene::Update(dt);

    VIEW_MGR.WorldToIso(isoTile->GetIsoTileSize(), isoTile->GetScale());

    sf::Vector2f mPos = ScreenToWorld(InputMgr::GetMousePosition());
    if (InputMgr::GetMouseButton(sf::Mouse::Left))
    {
        rect2.setPosition(mPos);
    }

    if (InputMgr::GetMouseButton(sf::Mouse::Right))
    {
        if (Utils::PointInTransformBounds(rect1, rect1.getLocalBounds(), mPos))
        { 
            rect1.setFillColor(sf::Color::Blue); 
        }
        else
        {
            rect1.setFillColor(sf::Color::Red);
        }
    }

    if (Utils::CheckCollision(rect1, rect2))
    {
        rect2.setFillColor(sf::Color::Red);
    }
    else
    {
        rect2.setFillColor(sf::Color::Green);
    }

    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        SCENE_MGR.ChangeScene(SceneIds::Dev2);
    }
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
    const sf::View& saveView = window.getView(); // saveView ¿ùµåºä·Î ¹Þ¾Æ¿È
    window.setView(VIEW_MGR.GetWorldView());
    VIEW_MGR.Draw(window);
    window.setView(saveView);
}

sf::Vector2f SceneDev1::GetIsoTileSize()
{
    return isoTile->GetIsoTileSize();
}

sf::Vector2f SceneDev1::GetIsoTileScale()
{
    return isoTile->GetScale();
}
