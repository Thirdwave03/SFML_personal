#include "stdafx.h"
#include "GameMgr.h"

void GameMgr::AddCoin(int addCoin)
{
	this->coin += addCoin;
	SOUND_MGR.PlaySfx("sound/getCoin.wav");
}


void GameMgr::Init()
{
	Reset();
	SetWaypointMap();
	SetStageDataMap();
}

void GameMgr::Reset()
{
	life = 10;
	coin = 30;
	currentStage = 1;
}

void GameMgr::SetWaypointMap()
{
	//waypointMap.insert({ 0,{1,6} });
	waypointMap.insert({ 1,{6,16} });
	waypointMap.insert({ 2,{4,20} });
	waypointMap.insert({ 3,{2,16} });
	waypointMap.insert({ 4,{8,4} });
	waypointMap.insert({ 5,{12,12} });
	waypointMap.insert({ 6,{10,16} });
	waypointMap.insert({ 7,{3,2} });
	waypointMap.insert({ 8,{2,1} });
}

void GameMgr::SetStageDataMap()
{
	SetStage0();
	SetStage1();
	SetStage2();
	SetStage3();
	SetStage4();
	SetStage5();
}

void GameMgr::SetStage0()
{
	for (int i = 0; i < 2; i++)
	{
		stageDataMap[0].push_back(0);
		stageDataMap[0].push_back(1);
		stageDataMap[0].push_back(2);
		stageDataMap[0].push_back(3);
	}
	stageDataMap[0].push_back(0);
	stageDataMap[0].push_back(0);
	stageDataMap[0].push_back(1);
	stageDataMap[0].push_back(1);
	stageDataMap[0].push_back(2);
	stageDataMap[0].push_back(2);
	stageDataMap[0].push_back(3);
	stageDataMap[0].push_back(3);
}

void GameMgr::SetStage1()
{
	for (int i = 0; i < 20; i++) // 0 20 0 0 
	{
		stageDataMap[1].push_back(1);
	}
}

void GameMgr::SetStage2()
{
	for (int i = 0; i < 4; i++) // 4 16 0 0
	{
		stageDataMap[2].push_back(1);
		stageDataMap[2].push_back(1);
		stageDataMap[2].push_back(1);
		stageDataMap[2].push_back(1);
		stageDataMap[2].push_back(0);
	}
}

void GameMgr::SetStage3()
{
	for (int i = 0; i < 5; i++) // 5 10 0 5
	{
		stageDataMap[3].push_back(1);
		stageDataMap[3].push_back(1);
		stageDataMap[3].push_back(0);
		stageDataMap[3].push_back(3);
	}
}

void GameMgr::SetStage4()
{
	for (int i = 0; i < 4; i++) // 10 5 5 5
	{
		stageDataMap[4].push_back(0);
		stageDataMap[4].push_back(1);
		stageDataMap[4].push_back(0);
		stageDataMap[4].push_back(3);
		stageDataMap[4].push_back(2);
	}
}

void GameMgr::SetStage5()
{
	for (int i = 0; i < 4; i++) // 0 0 20 0
	{
		stageDataMap[5].push_back(2);
		stageDataMap[5].push_back(2);
		stageDataMap[5].push_back(2);
		stageDataMap[5].push_back(2);
		stageDataMap[5].push_back(2);
	}
}

sf::Vector2i GameMgr::GetWaypointMap(int index)
{	
	return waypointMap[index];
}

std::vector<int> GameMgr::GetStageData(int index)
{
	return stageDataMap[index];
}
