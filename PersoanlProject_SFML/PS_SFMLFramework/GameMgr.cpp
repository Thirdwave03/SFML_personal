#include "stdafx.h"
#include "GameMgr.h"

void GameMgr::Init()
{
	Reset();
}

void GameMgr::Reset()
{
	life = 10;
	coin = 30;
}
