#include "stdafx.h"
#include "IsometricTile.h"

IsometricTile::IsometricTile()
{
}

bool IsometricTile::SetIsoTile(const int* tileType, sf::Vector2i count)
{
	if (!TEXTURE_MGR.Load(tileTexId))
		return false;
	texture = &TEXTURE_MGR.Get(tileTexId);

	tileCnt = count;
	vaTile.setPrimitiveType(sf::PrimitiveType::Triangles);
	vaTile.resize(count.x * count.y * 6);
	
	for (int i = 0; i < count.x; i++)
	{
		bool isEvenRow = false;
		for (int j = 0; j < count.y; j++)
		{			
			int tileNo = tileType[i + j * count.x];
			
			int tileCoordXIndex = tileNo % 3; // no of tiles in vertical
			int tileCoordYIndex = tileNo / 3; // to be added later
				
			// using triangle to draw single square shape requires 6 vertices
			sf::Vertex* triangles = &vaTile[(i + j * count.x) * 6];
			
			triangles[0].position = sf::Vector2f(i * 64.f + (int)isEvenRow * 32.f, (j + 1) * 16.f);
			triangles[1].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, j * 16.f);
			triangles[2].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, (j+2) * 16.f);
			triangles[3].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, j * 16.f);
			triangles[4].position = sf::Vector2f(32.f + i * 64.f + (int)isEvenRow * 32.f, (j + 2) * 16.f);
			triangles[5].position = sf::Vector2f((i+1) * 64.f + (int)isEvenRow * 32.f, (j + 1) * 16.f);

			triangles[0].texCoords = sf::Vector2f(tileCoordXIndex * 64.f, (tileCoordYIndex + 1) * 16.f);
			triangles[1].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, tileCoordYIndex * 16.f);
			triangles[2].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, (tileCoordYIndex + 2) * 16.f);
			triangles[3].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, tileCoordYIndex * 16.f);
			triangles[4].texCoords = sf::Vector2f(32.f + tileCoordXIndex * 64.f, (tileCoordYIndex + 2) * 16.f);
			triangles[5].texCoords = sf::Vector2f((tileCoordXIndex+1) * 64.f, (tileCoordYIndex + 1) * 16.f);
			isEvenRow = !isEvenRow;
		}
	}
	return true;
}

void IsometricTile::SetIsoLine()
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
				vaLineToBR[i * 2 + 0].position = sf::Vector2f(32.f + i * 64.f, 0.f);
				vaLineToBR[i * 2 + 1].position = sf::Vector2f((i + (tileCnt.y + 2) / 2.f) * 64.f, (tileCnt.y + 1) * 16.f);
			}
			else
			{
				auto temp = ((tileCnt.y - 1) / 2) - (tileCnt.x - 2 - i);
				vaLineToBR[i * 2 + 0].position = sf::Vector2f(32.f + i * 64.f, 0.f);
				vaLineToBR[i * 2 + 1].position = sf::Vector2f((i - temp + (tileCnt.y + 3) / 2.f) * 64.f, (tileCnt.y + 2 - 2 * temp) * 16.f);
			}

			if (i - 2 >= (tileCnt.y - 1) / 2)
			{
				vaLineToBL[i * 2 + 0].position = sf::Vector2f(32.f + (i) * 64.f, 0);
				vaLineToBL[i * 2 + 0].color = sf::Color::Magenta;
				vaLineToBL[i * 2 + 1].position = sf::Vector2f((i - (tileCnt.y) / 2.f) * 64.f, (tileCnt.y + 1) * 16.f);
				vaLineToBL[i * 2 + 1].color = sf::Color::Magenta;
			}
			else
			{
				auto temp = ((tileCnt.y - 1) / 2) - (i - 1);
				vaLineToBL[i * 2 + 0].position = sf::Vector2f(32.f + (i) * 64.f, 0);
				vaLineToBL[i * 2 + 0].color = sf::Color::Magenta;
				vaLineToBL[i * 2 + 1].position = sf::Vector2f((i + temp - (tileCnt.y) / 2.f) * 64.f, (tileCnt.y + 1 - 2 * temp) * 16.f);
				vaLineToBL[i * 2 + 1].color = sf::Color::Magenta;
			}
		}
		else if (tileCnt.x > tileCnt.y)
		{
			/*if (tileCnt.y % 2 == 0)
			{*/
				vaLineToBR[tileCnt.x * 2 + j * 2].position = sf::Vector2f(0.f, j * 32.f + 16.f);
				vaLineToBR[tileCnt.x * 2 + j * 2 + 1].position = sf::Vector2f(tileCnt.y * 32.f - j * 64.f, (tileCnt.y + 1) * 16.f);
				vaLineToBL[tileCnt.x * 2 + j * 2].position = sf::Vector2f(tileCnt.x * 64.f + 32.f, j * 32.f);
				vaLineToBL[tileCnt.x * 2 + j * 2].color = sf::Color::Magenta;
				vaLineToBL[tileCnt.x * 2 + j * 2 + 1].position = sf::Vector2f(tileCnt.x * 64 - (tileCnt.y * 32.f - j * 64.f), (tileCnt.y + 1) * 16.f);
				vaLineToBL[tileCnt.x * 2 + j * 2 + 1].color = sf::Color::Magenta;
				j++;
			/*}
			else
			{


			}*/
		}
	}	
}


void IsometricTile::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void IsometricTile::Release()
{
}

void IsometricTile::Reset()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void IsometricTile::Update(float dt)
{
}

void IsometricTile::Draw(sf::RenderWindow& window)
{
	sf::RenderStates rs;
	rs.texture = this->texture;
	window.draw(vaTile, rs);
	window.draw(vaLineToBL);
	window.draw(vaLineToBR);
}
