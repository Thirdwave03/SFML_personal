#include "stdafx.h"
#include "Bug.h"

Bug::Bug(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Bug::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	bugSprite.setPosition(position);
}

void Bug::SetRotation(float angle)
{
	rotation = angle;
	bugSprite.setRotation(rotation);
}

void Bug::SetScale(const sf::Vector2f& s)
{
	scale = s;
	bugSprite.setScale(scale);
}

void Bug::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(bugSprite, originPreset);
	}
}

void Bug::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	bugSprite.setOrigin(origin);
}

void Bug::OnDamage(int damage)
{
	hp -= damage;
	hp = Utils::Clamp(hp, 0, maxHp);
	if (hp == 0)
		OnDie();
}

void Bug::OnDie()
{
	isDead = true;
	GAME_MGR.AddCoin(gold);
}

void Bug::SetType(int bugTypeId)
{
	SetActive(true);
	this->bugType = (BugTypes)bugTypeId;
	auto bData = BUG_TABLE->Get(bugType);
	textureId = bData.textureId;
	bugName = bData.bugName;
	maxHp = bData.maxHp;
	speed = bData.speed;
	damage = bData.damage;
	gold = bData.gold;
	animationDuration = bData.animationDuration;
	layerType = bData.layerType;
	description = bData.description;
	description2 = bData.description2;
	description3 = bData.description3;	

	bugSprite.setTexture(TEXTURE_MGR.Get(textureId), true);

	Reset();
}

void Bug::OnArrival()
{
	GAME_MGR.SetLife(GAME_MGR.GetLife() -1);
	SetActive(false);
}

bool Bug::GetActive()
{
	return active;
}

void Bug::Init()
{
	Reset();
}

void Bug::Release()
{

}

void Bug::Reset()
{
	SetActive(true);
	isDead = false;
	auto a = bugSprite.getColor();
	bugSprite.setColor({ a.r,a.g,a.b,255 });

	speedMultiplier = 1.f;
	hp = maxHp;
	gold = 2;
	deadTimer = 3.f;

	accumTime = 0;
	waypointIndex = 1;

	hpBar.setSize({ 100.f,20.f });
	hpBar.setFillColor(sf::Color(255, 0, 0, 180));
	hpBar.setOutlineColor(sf::Color(120,120,120,120));
	hpBar.setOutlineThickness(2.5f);
	Utils::SetOrigin(hpBar, Origins::ML);

	maxhpBar.setSize({ 100.f,20.f });
	maxhpBar.setFillColor(sf::Color(60, 60, 60, 80));
	maxhpBar.setOutlineColor(sf::Color::Transparent);
	maxhpBar.setOutlineThickness(2.5f);
	Utils::SetOrigin(maxhpBar, Origins::ML);

	UpdateAnimation(0.f);
	SetScale({ 2.f,2.f });
	origin = Utils::SetOrigin5SQ(bugSprite, Origin5SQ::o23);
}

void Bug::Update(float dt)
{
	if (!isDead)
	{
		UpdateAnimation(dt);
		UpdateDirection(dt);
		SetPosition(position + direction * speed * speedMultiplier * dt);
		UpdateHealthBar(dt);
	}	
	
	if (isDead)
	{
		animationTarget = { 0, 128, 64, 64 };
		bugSprite.setTextureRect(animationTarget);
		auto a = bugSprite.getColor();
		sf::Uint8 temp = 255 / 3 * deadTimer;
		bugSprite.setColor({ a.r,a.g,a.b, temp });
		deadTimer -= dt;
	}

	if (deadTimer < 0 && isDead)
	{
		SetActive(false);
	}
}

void Bug::UpdateDirection(float dt)
{
	direction = Utils::GetNormal(VIEW_MGR.NonModifiedIsoWorldPos(destinationTile) - position);
	if (Utils::Distance(VIEW_MGR.NonModifiedIsoWorldPos(destinationTile), position) < 2.f)
	{
		SetDestinationTile(GAME_MGR.GetWaypointMap(waypointIndex));
		waypointIndex++;
		if (waypointIndex > GAME_MGR.GetWaypointCnt())
			OnArrival();
	}
}

void Bug::UpdateAnimation(float dt)
{	
	accumTime += dt * speedMultiplier;
	if (accumTime > animationDuration)
	{
		accumTime -= animationDuration;
		animationFlagH = !animationFlagH;
	}
	int scaleflag = 1;
	if (direction.x < 0)
	{
		scaleflag = -1;
	}
	if (direction.y < 0)
	{
		animationFlagV = true;
	}
	else
	{
		animationFlagV = false;
	}

	animationTarget = { 64 * animationFlagH, 64 * animationFlagV, 64,  64 };
	bugSprite.setTextureRect(animationTarget);
	bugSprite.setScale({ 2.f * scaleflag,2.f});
}

void Bug::UpdateHealthBar(float dt)
{
	auto a = maxhpBar.getSize();
	float hpPercent = (float)hp / (float)maxHp * 100.f;
	hpBar.setPosition(position.x-45.f, position.y + 60.f);
	maxhpBar.setPosition(position.x-45.f, position.y + 60.f);
	hpBar.setSize({ a.x * hpPercent / 100, a.y });
	Utils::SetOrigin(hpBar, Origins::ML);
}

void Bug::Draw(sf::RenderWindow& window)
{
	window.draw(bugSprite);
	window.draw(hpBar);
	window.draw(maxhpBar);
}
