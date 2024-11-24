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
	SetActive(false);
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
	upgradableTowers = tData.upgradableTowers;
	attackType = tData.attackType;
	slow = tData.slow;
	stun = tData.stun;
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
	case 0: // ElecRocq
		Fire_ElectricRocquet();
		break;
	case 1: // SprayF
		Fire_Spray();
		break;
	case 2: // SprayR
		Fire_Spray();
		break;
	case 3: // MosqRep
		Fire_MosquitoRepellent();
		break;
	case 4: // ElecRocqS
		Fire_ElectricRocquet();
		break;
	case 5: // UVRep
		Fire_UVRepellent();
		break;
	case 6: // ElecRocqU
		Fire_ElectricRocquet();
		break;
	case 7: // Lightning		*************
		Fire_Lightening();
		break;
	case 8: // TeslaCoil
		Fire_TeslaCoil();
		break;
	case 9: // SprayFS
		Fire_Spray();
		break;
	case 10: // SprayIce
		Fire_SprayFreeze();
		break;
	case 11: // Ice				*************
		Fire_Ice(); // To be Updated
		break;
	case 12: // SprayTorch
		Fire_SprayR();			// To be Updated
		break;
	case 13: // Fire			*************
		Fire_Fire(); // To be Updated
		break;
	case 14: // HomeMat
		Fire_MosquitoRepellent();
		break;
	case 15: // HomeMatS
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
	sprayStraw.setPosition(position.x, position.y - 130.f);
	switch (towerType)
	{
	case Types::ElectricRocquet:
		elecRocquetEffect.setPosition(position);
		break;
	case Types::SprayF:
	case Types::SprayR:
		sprayStraw.setPosition(position.x, position.y - 130.f);
		break;
	case Types::MosquitoRepellent:

		break;
	}
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
	SetActive(true);
	sortingOrder = 0;
	sortingLayer = SortingLayers::Foreground;
	originPreset = Origins::BC;
	attackTimer = 5;
	SetOrigin(originPreset);
	SetScale({ 3.f,3.f });
	name = "Tower";
	Utils::SetOrigin(sprayStraw, Origins::ML);
	SetRangeCircle();

	switch (towerType)
	{
	case Types::ElectricRocquet:
	case Types::ElectricRocquetS:
	case Types::ElectricRocquetU:
		elecRocquetEffect.setTexture(TEXTURE_MGR.Get("graphics/electricRocquet_effect.png"));
		elecRocquetEffect.setScale(3.f, 3.f);
		elecRocquetEffect.setPosition(position);
		elecRocquetEffect.setOrigin(origin);
		electricEffectOnEnemy.setTexture(TEXTURE_MGR.Get("graphics/electricRocquet_effect_on_Enemy.png"));
		electricEffectOnEnemy.setScale(2.5f, 2.5f);
		Utils::SetOrigin5SQOutBound(electricEffectOnEnemy, Origin5SQ::o24);
		break;
	case Types::SprayF:
	case Types::SprayR:
	case Types::SprayFS:
	case Types::SprayFreeze:
	case Types::SprayTorch:
		fireEffects.setPrimitiveType(sf::PrimitiveType::Triangles);
		fireEffects.resize(3);
		sprayStraw.setTexture(TEXTURE_MGR.Get("graphics/SprayStraw.png"));
		sprayStraw.setScale({ 3.f,3.f });
		break;
	case Types::Lightning:
		lighteningEffectOnEnemy.setTexture(TEXTURE_MGR.Get("graphics/Lightening_Effect.png"));
		lighteningEffectOnEnemy.setScale(3.0f, 3.0f);
		Utils::SetOrigin5SQOutBound(electricEffectOnEnemy, Origin5SQ::o24);
	case Types::MosquitoRepellent:
		mosquitoRepellentEffect.setTexture(TEXTURE_MGR.Get("graphics/MosquitoRepellent_effect.png"));
		mosquitoRepellentEffect.setScale(3.f, 3.f);
		mosquitoRepellentEffect.setPosition(position);
		mosquitoRepellentEffect.setOrigin(origin);
	case Types::HomeMat:
	case Types::HomeMatS:
		homeMatEffect.setTexture(TEXTURE_MGR.Get("graphics/HomeMat_effect.png"));
		homeMatEffect.setScale(3.f, 3.f);
		homeMatEffect.setPosition(position);
		homeMatEffect.setOrigin(origin);
		break;
	case Types::TeslaCoil:
		teslaCoilEffect.setTexture(TEXTURE_MGR.Get("graphics/TeslaCoil_effect.png"));
		teslaCoilEffect.setScale(3.f, 3.f);
		teslaCoilEffect.setPosition(position);
		teslaCoilEffect.setOrigin(origin);
	case Types::UVRepellent:
		UVRepellentEffect.setTexture(TEXTURE_MGR.Get("graphics/UVRepellent_effect.png"));
		UVRepellentEffect.setScale(3.f, 3.f);
		UVRepellentEffect.setPosition(position);
		UVRepellentEffect.setOrigin(origin);
		break;
	case Types::Fire:
		fireEffect.setTexture(TEXTURE_MGR.Get("graphics/Fire_effect.png"));
		fireEffect.setScale(9.0f, 6.0f);
		fireEffect.setPosition(position);
		Utils::SetOrigin(fireEffect, Origins::MC);
		break;
	case Types::Ice:
		break;
	}
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
	if (attackTimer > attackDuration)
		attackTimer = attackDuration;
	
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
	if ((int)towerType == 0 || (int)towerType == 4 || (int)towerType == 6)
	{
		UpdateElecRocquetEffect(dt);
	}
	if ((int)towerType == 7)
	{
		UpdateLighteningEffect(dt);
	}
	if ((int)towerType == 1 || (int)towerType == 2 || (int)towerType == 9 || (int)towerType == 10)
	{
		if (target != nullptr)
		{
			UpdateSprayStraw(dt);
		}
			UpdateSprayEffect(dt);
	}
	if ((int)towerType == 12)
	{
		if (target != nullptr)
		{
			UpdateSprayStraw(dt);
		}
		UpdateSprayEffectR(dt);
	}
	if ((int)towerType == 3)
	{
		UpdateMosquitoRepellentEffect(dt);
	}
	if ((int)towerType == 5)
	{
		UpdateUVRepellentEffect(dt);
	}
	if ((int)towerType == 14 || (int)towerType == 15)
	{
		UpdateHomeMatEffect(dt);
	}
	if ((int)towerType == 8)
	{
		UpdateTeslaCoilEffect(dt);
	}
	if ((int)towerType == 11)
	{
		UpdateIceEffect(dt);
	}
	if ((int)towerType == 13)
	{
		UpdateFireEffect(dt);
	}
}

void Towers::UpdateSprayStraw(float dt)
{	
	sprayStraw.setRotation(Utils::Angle(Utils::GetNormal(target->GetPosition() - sprayStraw.getPosition())));
}

void Towers::UpdateSprayEffect(float dt)
{
	fireEffects[0].color = sf::Color(255,255,255,0);
	fireEffects[1].color = sf::Color::Transparent;
	fireEffects[2].color = sf::Color::Transparent;
	if (attackTimer < 0.3)
	{
		for (sf::Uint8 i = 1; i < 3; i++)
		{
			sf::Uint8 opacity = 255 - attackTimer / 0.3 * 255;
			fireEffects[i].color = sf::Color({ 80, 220, 255, opacity });
		}
	}
}

void Towers::UpdateSprayEffectR(float dt)
{
	fireEffects[0].color = sf::Color(255, 255, 0, 0);
	fireEffects[1].color = sf::Color::Transparent;
	fireEffects[2].color = sf::Color::Transparent;
	if (attackTimer < 0.3)
	{
		for (sf::Uint8 i = 1; i < 3; i++)
		{
			sf::Uint8 opacity = 255 - attackTimer / 0.3 * 255;
			fireEffects[i].color = sf::Color({ 255, 0, 0, opacity });
		}
	}
}

void Towers::UpdateElecRocquetEffect(float dt)
{
	elecRocquetEffect.setColor(sf::Color::Transparent);
	sf::Uint8 opacity = 255 - (attackDuration - attackTimer) * 250 * (1/attackDuration);
	elecRocquetEffect.setColor({ 255,255,255, opacity });

	electricEffectOnEnemy.setColor(sf::Color::Transparent);
	if (attackTimer < 0.3)
	{
		sf::Uint8 opacity2 = 255 - attackTimer / 0.3 * 255;
		electricEffectOnEnemy.setColor({ 255, 255, 255, opacity2 });
	}
}

void Towers::UpdateLighteningEffect(float dt)
{
	lighteningEffectOnEnemy.setColor(sf::Color::Transparent);
	if (attackTimer < 0.3)
	{
		sf::Uint8 opacity2 = 255 - attackTimer / 0.3 * 255;
		lighteningEffectOnEnemy.setColor({ 255, 255, 255, opacity2 });
	}
}

void Towers::UpdateIceEffect(float dt)
{
	iceEffectOnEnemy.setColor(sf::Color::Transparent);
	if (attackTimer < 0.3)
	{
		sf::Uint8 opacity2 = 255 - attackTimer / 0.3 * 255;
		iceEffectOnEnemy.setColor({ 255, 255, 255, opacity2 });
	}
}

void Towers::UpdateFireEffect(float dt)
{
	fireEffect.setColor(sf::Color::Transparent);
	if (attackTimer < attackDuration / 2)
	{
		sf::Uint8 opacity = 150;
		fireEffect.setColor({ 255,255,255,opacity });
	}
	else
	{
		sf::Uint8 opacity = 150 - (attackTimer - attackDuration / 2) / (attackDuration / 2) * 150;
		fireEffect.setColor({ 255,255,255,opacity });
	}
}


void Towers::UpdateMosquitoRepellentEffect(float dt)
{
	mosquitoRepellentEffect.setColor(sf::Color::Transparent);
	if (attackTimer < attackDuration/2)
	{
		sf::Uint8 opacity = 200;
		mosquitoRepellentEffect.setColor({ 255,255,255,opacity });
	}
	else
	{
		sf::Uint8 opacity = 200 - (attackTimer-attackDuration/2) / (attackDuration/2) * 200;
		mosquitoRepellentEffect.setColor({ 255,255,255,opacity });
	}
}

void Towers::UpdateUVRepellentEffect(float dt)
{
	UVRepellentEffect.setColor(sf::Color::Transparent);
	if (attackTimer < attackDuration / 2)
	{
		sf::Uint8 opacity = 200;
		UVRepellentEffect.setColor({ 255,255,255,opacity });
	}
	else
	{
		sf::Uint8 opacity = 200 - (attackTimer - attackDuration / 2) / (attackDuration / 2) * 200;
		UVRepellentEffect.setColor({ 255,255,255,opacity });
	}
}

void Towers::UpdateHomeMatEffect(float dt)
{
	homeMatEffect.setColor(sf::Color::Transparent);
	if (attackTimer < attackDuration / 2)
	{
		sf::Uint8 opacity = 200;
		homeMatEffect.setColor({ 255,255,255,opacity });
	}
	else
	{
		sf::Uint8 opacity = 200 - (attackTimer - attackDuration / 2) / (attackDuration / 2) * 200;
		homeMatEffect.setColor({ 255,255,255,opacity });
	}
}

void Towers::UpdateTeslaCoilEffect(float dt)
{
	teslaCoilEffect.setColor(sf::Color::Transparent);
	if (attackTimer < attackDuration / 2)
	{
		sf::Uint8 opacity = 200;
		teslaCoilEffect.setColor({ 255,255,255,opacity });
	}
	else
	{
		sf::Uint8 opacity = 200 - (attackTimer - attackDuration / 2) / (attackDuration / 2) * 200;
		teslaCoilEffect.setColor({ 255,255,255,opacity });
	}
}

void Towers::Draw(sf::RenderWindow& window)
{
	if (isSelected)
	{
		window.draw(rangeCircle);
	}
	window.draw(towerSprite);
	if ((int)towerType == 1 || (int)towerType == 2 || (int)towerType == 9 || (int)towerType == 10 || (int)towerType == 12)
	{
		if (target != nullptr)
		{
			window.draw(sprayStraw);
			window.draw(fireEffects);
		}
	}
	else if ((int)towerType == 0 || (int)towerType == 4 || (int)towerType == 6)
	{ // 7 LighteningÀº ÀÓ½Ã
		window.draw(elecRocquetEffect);
		if (target != nullptr)
		{
			window.draw(electricEffectOnEnemy);
		}
	}
	else if ((int)towerType == 7)
	{
		if (target != nullptr)
		{
			window.draw(lighteningEffectOnEnemy);
		}
	}
	else if ((int)towerType == 3)
	{
		window.draw(mosquitoRepellentEffect);
	}
	else if ((int)towerType == 5)
	{
		window.draw(UVRepellentEffect);
	}
	else if ((int)towerType == 8)
	{
		window.draw(teslaCoilEffect);
	}
	else if ((int)towerType == 14 || (int)towerType == 15)
	{
		window.draw(homeMatEffect);
	}
	else if ((int)towerType == 11)
	{
		window.draw(iceEffectOnEnemy);
	}
	else if ((int)towerType == 13)
	{
		window.draw(fireEffect);
	}
}

void Towers::Fire_ElectricRocquet()
{
	target->OnDamage(damage);
	ElectricEffectOnEnemy();
	SOUND_MGR.PlaySfx("sound/elec.mp3");
}

void Towers::Fire_Lightening()
{
	target->OnDamage(damage);
	if (target->GetStunTimer() < stun)
		target->SetStunTimer(stun);
	LighteiningEffectOnEnemy();
	SOUND_MGR.PlaySfx("sound/lightening.mp3");
}

void Towers::Fire_Ice()
{	
	SOUND_MGR.PlaySfx("sound/freezing.mp3");
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto& bug : bList)
	{
		if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
		{
			bug->OnDamage(damage);
			if (bug->GetSlowTimer() < slow)
				bug->SetSlowTimer(slow);
		}
	}
	SOUND_MGR.PlaySfx("sound/freezing.mp3");
}

void Towers::Fire_Fire()
{
	SOUND_MGR.PlaySfx("sound/fire.wav");
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto& bug : bList)
	{
		if (attackType == AttackTypes::Ground && bug->GetBugLayerType() == Bug::BugLayerType::Ground)
		{
			if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
			{
				bug->OnDamage(damage);
			}
		}
	}
}

void Towers::Fire_Spray()
{
	target->OnDamage(damage);
	SprayEffect();
	SOUND_MGR.PlaySfx("sound/spray.mp3");
}

void Towers::Fire_SprayFreeze()
{
	target->OnDamage(damage);
	if (target->GetSlowTimer() < slow)
		target->SetSlowTimer(slow);
	SprayEffect();
	SOUND_MGR.PlaySfx("sound/spray.mp3");
}

void Towers::Fire_SprayR()
{
	target->OnDamage(damage);
	SprayEffectR();
	SOUND_MGR.PlaySfx("sound/spray.mp3");
}

void Towers::Fire_MosquitoRepellent()
{
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto& bug : bList)
	{
		if (bug->GetBugLayerType() == Bug::BugLayerType::Air)
		{
			if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
			{
				bug->OnDamage(damage);
			}
		}
	}
	SOUND_MGR.PlaySfx("sound/mqRepel.mp3");
}

void Towers::Fire_UVRepellent()
{
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto& bug : bList)
	{
		if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
		{
			bug->OnDamage(damage);
			if (bug->GetStunTimer() < stun)
				bug->SetStunTimer(stun);
		}
	}
	SOUND_MGR.PlaySfx("sound/UVR.mp3");
}

void Towers::Fire_TeslaCoil()
{
	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
	for (auto& bug : bList)
	{		
		if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
		{
			bug->OnDamage(damage);
			if (bug->GetStunTimer() < stun)
				bug->SetStunTimer(stun);
		}
	}
	SOUND_MGR.PlaySfx("sound/teslaCoil.mp3");
}

//void Towers::Fire_HomeMat()
//{
//	auto& bList = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene())->GetBugList();
//	for (auto& bug : bList)
//	{
//		if (bug->GetBugLayerType() == Bug::BugLayerType::Air)
//		{
//			if (Utils::DistanceWithIsoTileRatio(bug->GetPosition(), position) < 192.f * range)
//			{
//				bug->OnDamage(damage);
//			}
//		}
//	}
//	SOUND_MGR.PlaySfx("sound/mqRepel.mp3");
//}

void Towers::SprayEffect()
{
	fireEffects[0].color = sf::Color::Transparent;
	fireEffects[1].color = sf::Color(80, 220, 255, 160);
	fireEffects[2].color = sf::Color(80, 220, 255, 160);
	fireEffects[0].position = { position.x, position.y - 130.f };
	fireEffects[1].position = { target->GetPosition().x - 50.f, target->GetPosition().y };
	fireEffects[2].position = { target->GetPosition().x + 50.f, target->GetPosition().y };
}

void Towers::SprayEffectR()
{
	fireEffects[0].color = sf::Color(255,255,0,0);
	fireEffects[1].color = sf::Color(255, 0, 0, 160);
	fireEffects[2].color = sf::Color(255, 0, 0, 160);
	fireEffects[0].position = { position.x, position.y - 130.f };
	fireEffects[1].position = { target->GetPosition().x - 50.f, target->GetPosition().y };
	fireEffects[2].position = { target->GetPosition().x + 50.f, target->GetPosition().y };
}

void Towers::ElectricEffectOnEnemy()
{
	electricEffectOnEnemy.setPosition(target->GetPosition());
	electricEffectOnEnemy.setColor(sf::Color::White);
	if (target->GetBugLayerType() == Bug::BugLayerType::Ground)
		Utils::SetOrigin5SQ(electricEffectOnEnemy, Origin5SQ::o23);
	else
		Utils::SetOrigin5SQOutBound(electricEffectOnEnemy, Origin5SQ::o24);

}

void Towers::LighteiningEffectOnEnemy()
{
	lighteningEffectOnEnemy.setPosition(target->GetPosition());
	lighteningEffectOnEnemy.setColor(sf::Color::White);
	if (target->GetBugLayerType() == Bug::BugLayerType::Ground)
		Utils::SetOrigin5SQ(lighteningEffectOnEnemy, Origin5SQ::o24);
	else
		Utils::SetOrigin5SQOutBound(lighteningEffectOnEnemy, Origin5SQ::o24);
}

void Towers::IceEffectOnEnemy()
{
	iceEffectOnEnemy.setPosition(target->GetPosition());
	iceEffectOnEnemy.setColor(sf::Color::White);
	if (target->GetBugLayerType() == Bug::BugLayerType::Ground)
		Utils::SetOrigin5SQ(iceEffectOnEnemy, Origin5SQ::o23);
	else
		Utils::SetOrigin5SQOutBound(iceEffectOnEnemy, Origin5SQ::o24);
}

void Towers::FireEffectOnEnemy()
{
	fireEffect.setPosition(target->GetPosition());
	fireEffect.setColor(sf::Color::White);
	if (target->GetBugLayerType() == Bug::BugLayerType::Ground)
	{
		Utils::SetOrigin5SQ(fireEffect, Origin5SQ::o23);
		Utils::SetOrigin5SQOutBound(fireEffect, Origin5SQ::o23);
	}
	
	else
		Utils::SetOrigin5SQOutBound(fireEffect, Origin5SQ::o24);
}
