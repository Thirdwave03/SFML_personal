#include "stdafx.h"
#include "IsometricTileMap.h"

IsometricTileMap::IsometricTileMap()
{

}

bool IsometricTileMap::SetIsoTile(std::unordered_map<int, std::vector<int>>& tileType, sf::Vector2i count, sf::Vector2f scale)
{
	if (!TEXTURE_MGR.Load(tileTexId))
		return false;
	texture = &TEXTURE_MGR.Get(tileTexId);

	vaTileRS.texture = texture;
	SetScale(scale);
	SetTileCnt(count);
	SetLoadedTileType(tileType);

	vaTile.setPrimitiveType(sf::PrimitiveType::Triangles);
	vaTile.resize(count.x * count.y * 6);
	
	//for (int i = 0; i < count.x; i++)
	//{
	//	bool isEvenRow = false;
	//	for (int j = 0; j < count.y; j++)
	//	{			
	//		int tileNo = tileType[i + j * count.x];
	//		
	//		int tileCoordXIndex = tileNo % 3; // no of tiles in vertical
	//		int tileCoordYIndex = tileNo / 3; // to be added later
	//			
	//		// using triangle to draw single square shape requires 6 vertices
	//		sf::Vertex* triangles = &vaTile[(i + j * count.x) * 6];
	//		
	//		triangles[0].position = sf::Vector2f(i * 64.f + (int)isEvenRow * 32.f, (j + 1) * 16.f);
	//		triangles[1].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, j * 16.f);
	//		triangles[2].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, (j+2) * 16.f);
	//		triangles[3].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, j * 16.f);
	//		triangles[4].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, (j + 2) * 16.f);
	//		triangles[5].position = sf::Vector2f((i+1) * 64.f + (int)isEvenRow * 32.f, (j + 1) * 16.f);

	//		triangles[0].texCoords = sf::Vector2f(tileCoordXIndex * 64.f, (tileCoordYIndex + 1) * 16.f);
	//		triangles[1].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, tileCoordYIndex * 16.f);
	//		triangles[2].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, (tileCoordYIndex + 2) * 16.f);
	//		triangles[3].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, tileCoordYIndex * 16.f);
	//		triangles[4].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, (tileCoordYIndex + 2) * 16.f);
	//		triangles[5].texCoords = sf::Vector2f((tileCoordXIndex+1) * 64.f, (tileCoordYIndex + 1) * 16.f);
	//		isEvenRow = !isEvenRow;
	//	}
	//}
	for (int i = 0; i < count.x; i++)
	{
		bool isEvenRow = false;
		for (int j = 0; j < count.y; j++)
		{
			int tileNo = tileType[j][i];

			int tileCoordXIndex = tileNo % 3; // no of tiles in vertical
			int tileCoordYIndex = tileNo / 3; // to be added later

			// using triangle to draw single square shape requires 6 vertices
			sf::Vertex* triangles = &vaTile[(i + j * count.x) * 6];

			triangles[0].position = sf::Vector2f(i * 64.f + (int)isEvenRow * 32.f, (j + 1) * 16.f);
			triangles[1].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, j * 16.f);
			triangles[2].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, (j + 2) * 16.f);
			triangles[3].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, j * 16.f);
			triangles[4].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, (j + 2) * 16.f);
			triangles[5].position = sf::Vector2f((i + 1) * 64.f + (int)isEvenRow * 32.f, (j + 1) * 16.f);

			triangles[0].texCoords = sf::Vector2f(tileCoordXIndex * 64.f, (tileCoordYIndex) * 32.f + 16.f);
			triangles[1].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, tileCoordYIndex * 32.f);
			triangles[2].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, (tileCoordYIndex) * 32.f + 32.f);
			triangles[3].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, tileCoordYIndex * 32.f);
			triangles[4].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, (tileCoordYIndex) * 32.f + 32.f);
			triangles[5].texCoords = sf::Vector2f((tileCoordXIndex + 1) * 64.f, (tileCoordYIndex) * 32.f + 16.f);
			isEvenRow = !isEvenRow;
		}
	}
	return true;
}

void IsometricTileMap::SetIsoLine()
{
	vaLineToBR.setPrimitiveType(sf::Lines);
	vaLineToBR.resize((tileCnt.x + tileCnt.y) * 2);
	vaLineToBL.setPrimitiveType(sf::Lines);
	vaLineToBL.resize((tileCnt.x + tileCnt.y) * 2);

	int j = 0;

	for (int i = 0; i < tileCnt.x + (tileCnt.y)/2+1; i++)
	{
		if (i < tileCnt.x)
		{
			if (tileCnt.x - 2 - i >= ((tileCnt.y - 1) / 2))
			{
				vaLineToBR[i * 2 + 0].position = sf::Vector2f((tileSize.x * scale.x)/2 + i * (tileSize.x * scale.x), 0.f);
				vaLineToBR[i * 2 + 1].position = sf::Vector2f((i + (tileCnt.y + 2) / 2.f) * (tileSize.x * scale.x), (tileCnt.y + 1) * (tileSize.y * scale.y)/2);
			}
			else
			{
				auto temp = ((tileCnt.y - 1) / 2) - (tileCnt.x - 2 - i);
				vaLineToBR[i * 2 + 0].position = sf::Vector2f((tileSize.x * scale.x)/2 + i * (tileSize.x * scale.x), 0.f);
				vaLineToBR[i * 2 + 1].position = sf::Vector2f((i - temp + (tileCnt.y + 3) / 2.f) * (tileSize.x * scale.x), (tileCnt.y + 2 - 2 * temp) * (tileSize.y * scale.y)/2);
			}

			if (i - 2 >= (tileCnt.y - 1) / 2)
			{
				vaLineToBL[i * 2 + 0].position = sf::Vector2f((tileSize.x * scale.x)/2 + (i) * (tileSize.x * scale.x), 0);
				vaLineToBL[i * 2 + 0].color = sf::Color::Magenta;
				vaLineToBL[i * 2 + 1].position = sf::Vector2f((i - (tileCnt.y) / 2.f) * (tileSize.x * scale.x), (tileCnt.y + 1) * (tileSize.y * scale.y)/2);
				vaLineToBL[i * 2 + 1].color = sf::Color::Magenta;
			}
			else
			{
				auto temp = ((tileCnt.y - 1) / 2) - (i - 1);
				vaLineToBL[i * 2 + 0].position = sf::Vector2f((tileSize.x * scale.x)/2 + (i) * (tileSize.x * scale.x), 0);
				vaLineToBL[i * 2 + 0].color = sf::Color::Magenta;
				vaLineToBL[i * 2 + 1].position = sf::Vector2f((i + temp - (tileCnt.y) / 2.f) * (tileSize.x * scale.x), (tileCnt.y + 1 - 2 * temp) * (tileSize.y * scale.y)/2);
				vaLineToBL[i * 2 + 1].color = sf::Color::Magenta;
			}
		}
		else/* if (tileCnt.x > tileCnt.y)*/
		{
			/*if (tileCnt.y % 2 == 0)
			{*/
				vaLineToBR[tileCnt.x * 2 + j * 2].position = sf::Vector2f(0.f, j * (tileSize.x * scale.x)/2 + (tileSize.y * scale.y)/2);
				vaLineToBR[tileCnt.x * 2 + j * 2 + 1].position = sf::Vector2f(tileCnt.y * (tileSize.x * scale.x)/2 - j * (tileSize.x * scale.x), (tileCnt.y + 1) * (tileSize.y * scale.y)/2);
				vaLineToBL[tileCnt.x * 2 + j * 2].position = sf::Vector2f(tileCnt.x * (tileSize.x * scale.x) + (tileSize.x * scale.x)/2, j * (tileSize.x * scale.x)/2);
				vaLineToBL[tileCnt.x * 2 + j * 2].color = sf::Color::Magenta;
				vaLineToBL[tileCnt.x * 2 + j * 2 + 1].position = sf::Vector2f(tileCnt.x * (tileSize.x * scale.x) - (tileCnt.y * (tileSize.x * scale.x)/2 - j * (tileSize.x * scale.x)), (tileCnt.y + 1) * (tileSize.y * scale.y)/2);
				vaLineToBL[tileCnt.x * 2 + j * 2 + 1].color = sf::Color::Magenta;
				j++;
			/*}
			else
			{


			}*/
		}
	}	
}

void IsometricTileMap::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	vaTileRS.transform.scale(scale);
}

void IsometricTileMap::SetTileCnt(sf::Vector2i tileCnt)
{
	this->tileCnt = tileCnt;
}


void IsometricTileMap::SetLoadedTileType(std::unordered_map<int, std::vector<int>>& tileMap)
{
	this->tileTypeMap = tileMap;
}

void IsometricTileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void IsometricTileMap::Release()
{
}

void IsometricTileMap::Reset()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void IsometricTileMap::Update(float dt)
{

}

void IsometricTileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates rs;
	rs.texture = this->texture;
	//rs.transform.scale({ 2.f,2.f });
	window.draw(vaTile, vaTileRS);
	window.draw(vaLineToBL);
	window.draw(vaLineToBR);
}

sf::FloatRect IsometricTileMap::GetTileRect()
{
	return vaTile.getBounds();
}