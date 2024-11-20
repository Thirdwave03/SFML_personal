#include "stdafx.h"
#include "SceneDev1.h"
#include "UiHud.h"
#include "Towers.h"
#include "Bug.h"

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
    VIEW_MGR.AllignIsoTile(*isoTile);
    //isoTile->SetIsoTileTest();

    text->sortingLayer = SortingLayers::UI;
    text->Set(25, sf::Color::White);
    text->SetString("Dev 1");

    uiHud = AddGo(new UiHud("UiHud"));
    uiHud->Reset();

    isoTile->GetUiHud(*uiHud);
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
    for (auto tower : towers)
    {
        RemoveGo(tower);
        towerPool.Return(tower);
    }
    towers.clear();

    for (auto bug : bugs)
    {
        RemoveGo(bug);
        bugPool.Return(bug);
    }
    bugs.clear();

    Scene::Exit();
}

void SceneDev1::Update(float dt)
{
    Scene::Update(dt);

    VIEW_MGR.WorldToIso(isoTile->GetIsoTileSize(), isoTile->GetScale());
    
    sf::Vector2f mPos = ScreenToWorld(InputMgr::GetMousePosition());
    if (InputMgr::GetMouseButton(sf::Mouse::Left))
    {
        OnClickLeft();
    }
    if (InputMgr::GetMouseButton(sf::Mouse::Right))
    {
        OnClickRight();
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::F2))
    {
        SCENE_MGR.ChangeScene(SceneIds::Dev2);
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::F9))
    {
        uiHud->TurnDebugMode();
        isoTile->TurnDebugMode();
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::F8))
    {
        isoTile->TurnTileVisible();
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::F7))
    {
        SpawnBugTest(10);
    }

}

void SceneDev1::FixedUpdate(float dt)
{

    Scene::FixedUpdate(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
    const sf::View& saveView = window.getView(); // saveView ¿ùµåºä·Î ¹Þ¾Æ¿È
    window.setView(VIEW_MGR.GetWorldView());
    VIEW_MGR.Draw(window);
    window.setView(saveView);
}

void SceneDev1::OnClickLeft()
{
    if (selectedTower != nullptr)
    {
        selectedTower->SetSelected(false);
        selectedTower = nullptr;
        uiHud->SetNullSelectedTower();
    }
    if (!uiHud->IfMouseOnUi() && !uiHud->IfBuilding())
    {
        for (auto obj : gameObjects)
        {
            if (obj->GetName() == "Tower")
            {
                Towers* towerObj = dynamic_cast<Towers*>(obj);
                if (VIEW_MGR.GetIsoMousePos() == towerObj->GetIsoTileCoords())
                {
                    selectedTower = towerObj;
                    selectedTower->SetSelected(true);
                    uiHud->SetSelectedTower(towerObj);
                }
            }
        }        
    }   
}

void SceneDev1::OnClickRight()
{
    if (selectedTower != nullptr)
    {
        selectedTower->SetSelected(false);
        selectedTower = nullptr;
        uiHud->SetNullSelectedTower();
    }
}

sf::Vector2f SceneDev1::GetIsoTileSize()
{
    return isoTile->GetIsoTileSize();
}

sf::Vector2f SceneDev1::GetIsoTileScale()
{
    return isoTile->GetScale();
}

void SceneDev1::BuildTower()
{
    Towers* tower = towerPool.Take();
    towers.push_back(tower);

    tower->SetIsoTileCoords(VIEW_MGR.GetIsoMousePos());
    tower->SetType(uiHud->GetBuildingTower());
    AddGo(tower);
}

void SceneDev1::SpawnBugTest(int cnt, int num, float duration)
{
    Bug* bug = bugPool.Take();
    bugs.push_back(bug);

    bug->SetActive(true);
    bug->SetPosition(VIEW_MGR.IsoToWorld({ 1,6 }));
    bug->SetDestinationTile({ 6,16 });
    AddGo(bug);
}

