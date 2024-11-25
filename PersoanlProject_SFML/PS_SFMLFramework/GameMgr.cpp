#include "stdafx.h"
#include "GameMgr.h"

void GameMgr::SetLife(int life)
{
	this->life = life;
	life = Utils::Clamp(life, 0, 20);
}

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
	SetUpgradableInfoMap();
}

void GameMgr::Reset()
{
	life = 20;
	coin = 30;
	currentStage = 1;
	hpMultiplier = 1.f;
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
	SetStage0to5();
	SetStage6to10();
	SetStage11to20();
	SetStage21to30();
}

void GameMgr::SetUpgradableInfoMap()
{
	upgradableInfoMap[0].push_back(4);
	upgradableInfoMap[0].push_back(5);
	upgradableInfoMap[1].push_back(9);
	upgradableInfoMap[2].push_back(12);
	upgradableInfoMap[3].push_back(14);
	upgradableInfoMap[4].push_back(6);
	upgradableInfoMap[4].push_back(7);
	upgradableInfoMap[5].push_back(8);
	upgradableInfoMap[9].push_back(10);
	upgradableInfoMap[10].push_back(11);
	upgradableInfoMap[12].push_back(13);
	upgradableInfoMap[14].push_back(15);
	//upgradableInfoMap[15].push_back(16);
	//upgradableInfoMap[16].push_back(17);
}

void GameMgr::SetCurrentStage(int stage)
{
	currentStage = stage;
	hpMultiplier = 1.f + ((float)currentStage - 4)/5.f;				// 10 = 2.2
	
	if (currentStage >= 10)
	{
		hpMultiplier = 2.2f + (float)(currentStage - 10) / 2.5f;		// 20 = 2.2 + 4 // 6.2
	}
	if (currentStage >= 20)
	{
		hpMultiplier = 6.2f + (float)(currentStage - 20) / 1.5f;	// 30 = 6.2 + 6.66 12.67
	}
	if (currentStage >= 30)
	{
		hpMultiplier = 12.7f + (float)(currentStage - 30) / 0.8f;		// 40 = 12.7 + 12.5
	}
	if (currentStage >= 40)
	{
		hpMultiplier = 25.2f + (float)(currentStage - 30) / 0.5f;  // 45.2
	}
	if (hpMultiplier < 1.f)
		hpMultiplier = 1.f;

	if (currentStage <= 2)
	{
		hpMultiplier = 1.f - (0.6 - 0.2 * currentStage);
	}
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
	for (int i = 0; i < 10; i++) // 0 0 10 10
	{
		stageDataMap[5].push_back(2);
		stageDataMap[5].push_back(3);
	}
}

void GameMgr::SetStage0to5()
{
	SetStage0();
	SetStage1();
	SetStage2();
	SetStage3();
	SetStage4();
	SetStage5();
}

void GameMgr::SetStage6to10()
{
	for (int i = 0; i < 10; i++)
	{
		stageDataMap[6].push_back(1);
		stageDataMap[6].push_back(0);
	}
	for (int i = 0; i < 20; i++)
	{
		stageDataMap[7].push_back(0);		
	}
	for (int i = 0; i < 10; i++)
	{
		stageDataMap[8].push_back(3);
		stageDataMap[8].push_back(2);
	}
	for (int i = 0; i < 20; i++)
	{
		stageDataMap[9].push_back(2);
	}
	for (int i = 0; i < 10; i++)
	{
		stageDataMap[10].push_back(0);
	}
	for (int i = 0; i < 10; i++)
	{
		stageDataMap[10].push_back(2);
	}
}

void GameMgr::SetStage11to20()
{
	for (int i = 11; i <= 20; i++)
	{
		for (int j = 0; j < 5 ; j++)
		{
			stageDataMap[i].push_back(0);
			stageDataMap[i].push_back(2);
			stageDataMap[i].push_back(1);
			stageDataMap[i].push_back(3);
			stageDataMap[i].push_back(0);
		}
	}
}

void GameMgr::SetStage21to30()
{
	for (int i = 21; i <= 30; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			stageDataMap[i].push_back(0);
			stageDataMap[i].push_back(3);
			stageDataMap[i].push_back(1);
			stageDataMap[i].push_back(3);
			stageDataMap[i].push_back(0);
			stageDataMap[i].push_back(2);
		}
	}
}

void GameMgr::SetStage31to50()
{
	for (int i = 31; i <= 50; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			stageDataMap[i].push_back(0);
			stageDataMap[i].push_back(3);
			stageDataMap[i].push_back(0);
			stageDataMap[i].push_back(3);
			stageDataMap[i].push_back(0);
			stageDataMap[i].push_back(3);
		}
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

std::vector<int> GameMgr::GetUpgradableInfo(int index)
{
	return upgradableInfoMap[index];
}
