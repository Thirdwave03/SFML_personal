#include "stdafx.h"
#include "Towers.h"
#include "Bug.h"
#include "SceneDev1.h"

Towers::Towers(const std::string& name)
	:GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	originPreset = Origins::BC;
}

void Towers::Set()
{
}

void Towers::OnSell()
{
}

void Towers::OnConsturction()
{

}

void Towers::SetType(Types type)
{
	
	this->towerType = type;
	auto tData = TOWER_TABLE->Get(type);
	towerType = tData.towerType;
	textureId = tData.textureId;
	towerName = tData.towerName;
	damage = tData.damage;
	attackDuration = tData.attackDuration;
	range = tData.range;
	isAreaAttack = tData.isAreaAttack;
	price = tData.price;
	priceOnSell = tData.priceOnSell;
	isUpgradable = tData.isUpgradable;
	attackType = tData.attackType;
	bonusType = tData.bonusType;
	description = tData.description;
	description2 = tData.description2;
	description3 = tData.description3;

	towerSprite.setTexture(TEXTURE_MGR.Get(textureId), true); 		

	Reset();
}

void Towers::Fire()
{
	switch ((int)towerType)
	{
	case 0:
		Fire_ElectricRocquet();
		break;
	case 1:
		Fire_SprayF();
		break;
	case 2:
		Fire_SprayR();
		break;
	case 3:
		Fire_MosquitoRepellent();
		break;
	}
	attackTimer = 0;
}

void Towers::SetTarget()
{
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto bug : bList)
	{
		if(bug->GetHp() > 0)
		{
			if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
			{
				switch ((int)attackType)
				{
				case 0:
					target = bug;
					return;
					break;
				case 1:
					if (bug->GetBugLayerType() == Bug::BugLayerType::Ground)
					{
						target = bug;
						return;
					}
					else
						continue;
					break;
				case 2:
					if (bug->GetBugLayerType() == Bug::BugLayerType::Air)
					{
						target = bug;
						return;
					}
					else
						continue;
					break;
				}
			}// switch
		} // if (distance < range)
	}
}

void Towers::SetIsoTileCoords(sf::Vector2i isoCoord)
{
	isoTileCoords = isoCoord;
	SetPosition({ VIEW_MGR.NonModifiedIsoWorldPos(isoTileCoords).x, VIEW_MGR.NonModifiedIsoWorldPos(isoTileCoords).y + 20.f });
}

void Towers::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	towerSprite.setPosition(position);
	rangeCircle.setPosition(position);
}

void Towers::SetRotation(float angle)
{
}

void Towers::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	towerSprite.setScale(scale);
	
}

void Towers::SetRangeCircle()
{
	rangeCircle.setRadius(96.f*range);
	rangeCircle.setPosition(position);
	rangeCircle.setFillColor({ 0,0,255,60 });
	rangeCircle.setScale({ 2.f,1.f });
	Utils::SetOrigin(rangeCircle, Origins::MC);
}

void Towers::SetOrigin(Origins preset)
{
	this->originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(towerSprite, originPreset);
	}
}

void Towers::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	towerSprite.setOrigin(newOrigin);
}

void Towers::Init()
{
}

void Towers::Release()
{
}

void Towers::Reset()
{
	sortingOrder = 0;
	sortingLayer = SortingLayers::Foreground;
	originPreset = Origins::BC;
	attackTimer = 5;
	SetOrigin(originPreset);
	SetScale({ 3.f,3.f });
	name = "Tower";
	SetRangeCircle();
}

void Towers::Update(float dt)
{
	attackTimer += dt;
	if (target != nullptr)
	{
		if (attackTimer > attackDuration)
		{
			attackTimer = 0;
			Fire();
		}
		if (Utils::DistanceWithIsoTileRatio(target->GetPosition(), position) > 192.f * range)
		{
			target = nullptr;
		}
	}
	if (target != nullptr)
	{
		if (!target->GetActive())
		{
			target = nullptr;
		}
	}
	if (target != nullptr)
	{
		if (target->GetHp() <= 0)
		{
			target = nullptr;
		}
	}

	if (target == nullptr)
	{
		SetTarget();
	}

	if (attackDuration - attackTimer < 0.5)
	{
		sf::Color a = towerSprite.getColor();
		towerSprite.setColor({ a.r, a.g, a.b, 255 });
	}
	else
	{
		sf::Color a = towerSprite.getColor();
		towerSprite.setColor({ a.r, a.g, a.b, 120 });
	}
}

void Towers::Draw(sf::RenderWindow& window)
{
	if (isSelected)
	{
		window.draw(rangeCircle);
	}
	window.draw(towerSprite);
}

void Towers::Fire_ElectricRocquet()
{
	target->OnDamage(damage);
}

void Towers::Fire_SprayF()
{
	target->OnDamage(damage);
}

void Towers::Fire_SprayR()
{
	target->OnDamage(damage);
}

void Towers::Fire_MosquitoRepellent()
{
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto& bug : bList)
	{
		if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
		{
			bug->OnDamage(damage);
		}
	}
}
