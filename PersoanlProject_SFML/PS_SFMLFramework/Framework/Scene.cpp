#include "stdafx.h"
#include "Scene.h"
#include <functional>

Scene::Scene(SceneIds id)
	: id(id)
{

}

void Scene::Init()
{
	ApplyAddGo();
	ApplyRemoveGO();

	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyAddGo();
	ApplyRemoveGO();
}

void Scene::FixedUpdate(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->FixedUpdate(dt);
	}
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->Update(dt);
	}
}

void Scene::LateUpdate(float dt)
{
}

void Scene::OnPreDraw()
{
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawQueue;
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawUiQueue;

	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;

		if (obj->sortingLayer == SortingLayers::UI)
		{
			drawUiQueue.push(obj);
		}
		else
		{
			drawQueue.push(obj);
		}
	}

	//const sf::View& saveView = window.getView(); // saveView ¿ùµåºä·Î ¹Þ¾Æ¿È
	window.setView(VIEW_MGR.GetWorldView());

	while (!drawQueue.empty())
	{
		GameObject* obj = drawQueue.top();
		obj->Draw(window);
		drawQueue.pop();
	}

	/*TOWERBUILD_MGR*/

	window.setView(VIEW_MGR.GetUiView());
	window.draw(TIME_MGR.GetFrameText());
	while (!drawUiQueue.empty())
	{
		GameObject* obj = drawUiQueue.top();
		obj->Draw(window);
		drawUiQueue.pop();
	}

	window.setView(VIEW_MGR.GetCurrentView());
}

void Scene::OnPostDraw()
{
	ApplyAddGo();
	ApplyRemoveGO();
}

void Scene::RemoveGo(GameObject* obj)
{
	removeGameObjects.push_back(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	list.clear();
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			list.push_back(obj);
		}
	}
	return list.size();
}

void Scene::ApplyAddGo()
{
	for (auto go : addGameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addGameObjects.clear();
}

void Scene::ApplyRemoveGO()
{
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	// can be seen as : Pixel ( Screen ), Coords( x,y axis on WorldMap)
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, VIEW_MGR.GetWorldView());
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, VIEW_MGR.GetWorldView());
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, VIEW_MGR.GetUiView());
}

sf::Vector2i Scene::UIToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, VIEW_MGR.GetUiView());
}

void Scene::TurnDebugBox(bool active, sf::Color color)
{
	isDebugMode = active;
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->TurnDebugBox(active, color);
	}
}