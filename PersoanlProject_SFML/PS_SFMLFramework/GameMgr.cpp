#include "stdafx.h"
#include "GameMgr.h"

void GameMgr::Init()
{
	Reset();
	SetWaypointMap();
}

void GameMgr::Reset()
{
	life = 10;
	coin = 30;
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

sf::Vector2i GameMgr::GetWaypointMap(int index)
{	
	return waypointMap[index];
}