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
    isoTile = AddGo(new IsometricTileMap());

    
    //const int tileType[] =
    //{
    //    0, 1, 
    //    2, 0,
    //};
    SOUND_MGR.PlayBgm("sound/mandarin-calmly-music-2965.mp3" , true);
    isoTile->SetIsoTile(TILE_TABLE->GetTileMapTable(), TILE_TABLE->GetTileMapCount(), { 3.f,3.f });
    isoTile->SetIsoLine();
    isoTile->GetScale();
    isoTile->GetIsoTileSize();
    VIEW_MGR.SetViewBoundary(isoTile->GetTileRect(), isoTile->GetIsoTileSize(), isoTile->GetScale());
    VIEW_MGR.AllignIsoTile(*isoTile);
    //isoTile->SetIsoTileTest();

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
    if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
    {
        OnClickLeft();
    }
    if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
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
        SpawnBugTest(1);
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::Space))
    {
        if (GAME_MGR.GetCurrentStage() <= GAME_MGR.GetTotalStage())
            SetWaveSpawnQueue();
        else
            GAME_MGR.SetLife(0);
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::F5))
    {
        SOUND_MGR.PlayBgm("sound/mandarin-calmly-music-2965.mp3");
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::F6))
    {
        SOUND_MGR.StopBgm();
    }
    TIME_MGR.SetTimeScale(1.0f);
    if (InputMgr::GetKey(sf::Keyboard::Z))
    {
        TIME_MGR.SetTimeScale(2.0f);
    }

    if (isSpawning)
    {
        spawnTimer += dt;
        if (spawnTimer > spawnDuration)
        {
            spawnTimer = 0;
            SpawnBug(spawnQueue.front());
            spawnQueue.pop();
            spawnCnt--;
        }
    }
    if (spawnCnt <= 0)
    {
        isSpawning = false;
    }


    auto it = bugs.begin();
    while (it != bugs.end())
    {
        if (!(*it)->IsActive())
        {
            bugPool.Return(*it);
            RemoveGo(*it);
            it = bugs.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void SceneDev1::FixedUpdate(float dt)
{

    Scene::FixedUpdate(dt);
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
    const sf::View& saveView = window.getView(); // saveView ������ �޾ƿ�
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
    bug->SetPosition({ VIEW_MGR.NonModifiedIsoWorldPos({ 1,6 }).x, VIEW_MGR.NonModifiedIsoWorldPos({ 1,6 }).y});
    bug->SetDestinationTile({ 6,16 });
    AddGo(bug);
}

void SceneDev1::SpawnBug(int bugTypeId)
{
    Bug* bug = bugPool.Take();
    bugs.push_back(bug);

    bug->SetType(bugTypeId);
    bug->SetPosition({ VIEW_MGR.NonModifiedIsoWorldPos({ 1,6 }).x, VIEW_MGR.NonModifiedIsoWorldPos({ 1,6 }).y });
    bug->SetDestinationTile({ 6,16 });
    AddGo(bug);
}

void SceneDev1::SetWaveSpawnQueue()
{
    if (isSpawning)
        return;
    spawnTimer = 0;
    spawnCnt = GAME_MGR.GetStageData(GAME_MGR.GetCurrentStage()).size();
    isSpawning = true;
    for (int i = 0; i < spawnCnt; i++)
    {
        spawnQueue.push(GAME_MGR.GetStageData(GAME_MGR.GetCurrentStage())[i]);
    }
    GAME_MGR.SetCurrentStage(GAME_MGR.GetCurrentStage() + 1);
}

