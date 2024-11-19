#include "stdafx.h"
#include "ViewMgr.h"
#include "SceneDev1.h"

void ViewMgr::Init()
{
	Reset();
}

void ViewMgr::Update(float dt)
{	
	viewDirection.x = InputMgr::GetAxis(Axis::Horizontal);
	viewDirection.y = InputMgr::GetAxis(Axis::Vertical);
	float dirMagnitude = Utils::Magnitude(viewDirection);
	if (dirMagnitude > 1.f)
	{
		Utils::Normalize(viewDirection);
	}
	viewPos = viewPos + viewDirection * viewMoveSpeed * dt;
	viewSize = worldView.getSize();

	worldView.setCenter(viewPos);
	
	if (viewSize.x <= viewBoundary.width && viewSize.y <= viewBoundary.height)
	{
		sf::FloatRect viewRect = { worldView.getCenter().x - worldView.getSize().x / 2,worldView.getCenter().y - worldView.getSize().y / 2, worldView.getSize().x, worldView.getSize().y };

		if (viewRect.left < viewBoundary.left)
		{
			viewPos = { viewBoundary.left + worldView.getSize().x / 2,worldView.getCenter().y };
			worldView.setCenter(viewPos);
		}
		if (viewRect.left+viewRect.width > viewBoundary.left + viewBoundary.width)
		{
			viewPos = { viewBoundary.left + viewBoundary.width - worldView.getSize().x / 2,worldView.getCenter().y };
			worldView.setCenter(viewPos);
		}
		if (viewRect.top < viewBoundary.top)
		{
			viewPos = { worldView.getCenter().x , viewBoundary.top + worldView.getSize().y / 2};
			worldView.setCenter(viewPos);
		}
		if (viewRect.top + viewRect.height > viewBoundary.top + viewBoundary.height)
		{
			viewPos = { worldView.getCenter().x ,viewBoundary.top + viewBoundary.height - worldView.getSize().y / 2};
			worldView.setCenter(viewPos);
		}
	}

	SetScreenMousePos(InputMgr::GetMousePosition());
	mPosWorld = ScreenToWorld(mPosScreen);
}

void ViewMgr::Reset()
{
	auto wSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(wSize);
	uiView.setSize(wSize);
	editorView.setSize(wSize * 2.f);

	worldView.setCenter(0.f,0.f);
	uiView.setCenter(wSize / 2.f);
	editorView.setCenter(wSize);

	SetViewType(ViewTypes::WorldView);
}

void ViewMgr::Draw(sf::RenderWindow& window)
{
	ResetViewCheckRect();
	//window.draw(viewCheckRect);
}

sf::Vector2f ViewMgr::ScreenToWorld(sf::Vector2i screenPos)
{	
	auto tempMPos = FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, GetWorldView());
	SceneDev1* tempScene = (SceneDev1*)(SCENE_MGR.GetCurrentScene());
	tempMPos.x -= tempScene->GetIsoTileSize().x/2 * tempScene->GetIsoTileScale().x;
	tempMPos.y -= tempScene->GetIsoTileSize().y/2 * tempScene->GetIsoTileScale().y;
	return tempMPos;
}

sf::Vector2i ViewMgr::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, GetWorldView());
}

sf::Vector2i ViewMgr::WorldToIso(sf::Vector2f tileSize, sf::Vector2f tileScale)
{
	sf::Vector2i isoCoord;
	worldCoordFloatBR = mPosWorld.y - mPosWorld.x / 2.f;
	worldCoordFloatBL = mPosWorld.x/2.f + mPosWorld.y;
	devidedBR = worldCoordFloatBR + tileSize.y / 2.f * tileScale.y;
	devidedBL = worldCoordFloatBL + tileSize.y / 2.f * tileScale.y;
	while (devidedBR >= (tileSize.x * tileScale.x) / 2.f)
		devidedBR -= (tileSize.x * tileScale.x) / 2.f;
	while (devidedBR < 0)
		devidedBR += (tileSize.x * tileScale.x) / 2.f;
	while (devidedBL >= (tileSize.x * tileScale.x) / 2.f)
		devidedBL -= (tileSize.x * tileScale.x) / 2.f;
	float tempX = mPosWorld.x;
	float tempY = mPosWorld.y;
	xIndex = 0;
	yIndex = 0;
	while (tempX >= (tileSize.x * tileScale.x) / 2)
	{
		tempX -= (tileSize.x * tileScale.x) / 2;
		xIndex++;
	}
	while (tempY >= (tileSize.y * tileScale.y)/2)
	{
		tempY -= (tileSize.y * tileScale.y) / 2;
		yIndex++;
	}

	if (xIndex % 2 == 0)
	{
		if (yIndex % 2 == 0)
		{
			if (devidedBL < (tileSize.y * tileScale.y)/2.f)
			{
				mPosIso.x = xIndex / 2;
				mPosIso.y = yIndex;
			}
			else
			{
				mPosIso.x = xIndex / 2 - 1;
				mPosIso.y = yIndex - 1;
			}
		}
		else
		{
			if (devidedBR < (tileSize.y * tileScale.y) / 2.f)
			{
				mPosIso.x = xIndex / 2 - 1;
				mPosIso.y = yIndex;
			}
			else
			{
				mPosIso.x = xIndex / 2;
				mPosIso.y = yIndex - 1;
			}
		}
	}
	else
	{
		if (yIndex % 2 == 0)
		{
			if (devidedBR >= 32.f)
				mPosIso.y = yIndex - 1;
			else
				mPosIso.y = yIndex;
			mPosIso.x = xIndex / 2;
		}
		else
		{
			if (devidedBL < 32.f)
				mPosIso.y = yIndex;
			else
				mPosIso.y = yIndex-1;
			mPosIso.x = xIndex / 2;
		}
	}
	


	//if (((int)(mPosWorld.y + tileSize.y/2) / (int)(tileSize.y / 2.f * tileScale.y)) % 2 == 0)
	//isoCoord.x = mPosWorld.x / (tileSize.x * tileScale.x);
	//else
	//isoCoord.x = mPosWorld.x / (tileSize.x * tileScale.x) + 1;
	//	
	//if (((int)(mPosWorld.x + tileSize.x/2) / (int)(tileSize.x / 2.f * tileScale.x)) % 2 == 0)
	//isoCoord.y = mPosWorld.y / (tileSize.y / 2.f * tileScale.y);
	//else
	//isoCoord.y = mPosWorld.y / (tileSize.y / 2.f * tileScale.y) + 1;	


	return mPosIso;
}

sf::Vector2f ViewMgr::IsoToWorld(sf::Vector2i isoMouseCoord)
{
	return sf::Vector2f();
}

void ViewMgr::SetScreenMousePos(sf::Vector2i mPosScreen)
{
	this->mPosScreen = mPosScreen;
}

void ViewMgr::SetViewType(ViewTypes viewType)
{
	currentViewType = viewType;
	switch (currentViewType)
	{
	case ViewTypes::WorldView:
		currentView = worldView;
		break;
	case ViewTypes::UiView:
		currentView = uiView;
		break;
	case ViewTypes::EditorView:
		currentView = editorView;
		break;
	default:
		currentView = worldView;
		break;
	}
	FRAMEWORK.GetWindow().setView(currentView);
}

void ViewMgr::SetViewBoundary(sf::FloatRect viewBound, sf::Vector2f isoTileSize, sf::Vector2f isoScale)
{
	viewBoundary = viewBound;
	viewBoundary.left += isoTileSize.x/2;
	viewBoundary.width -= isoTileSize.x;
	viewBoundary.top += isoTileSize.y/2;
	viewBoundary.height -= isoTileSize.y;
	viewBoundary.left *= isoScale.x;
	viewBoundary.width *= isoScale.x;
	viewBoundary.top *= isoScale.y;
	viewBoundary.height *= isoScale.y;
}

void ViewMgr::ResetViewCheckRect()
{
	auto uvSize = worldView.getSize();
	auto uvCenterPos = viewPos;
	viewCheckRect.setSize({ uvSize.x, uvSize.y});
	viewCheckRect.setOutlineColor(sf::Color::Magenta);
	viewCheckRect.setFillColor(sf::Color::Transparent);
	viewCheckRect.setOutlineThickness(10.f);
	viewCheckRect.setPosition(uvCenterPos);
	Utils::SetOrigin(viewCheckRect, Origins::MC);
}

