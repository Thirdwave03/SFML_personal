#include "stdafx.h"
#include "TimeMgr.h"

void TimeMgr::Init()
{
    frameText.setFont(FONT_MGR.Get("fonts/DS-DIGI.ttf"));
    frameText.setPosition({ 50.f,50.f });
}

void TimeMgr::FrameCheck()
{
    currentFrameTime += realDeltaTime;
    currentFrame++;
    if (currentFrameTime >= 1.f)
    {
        frameText.setString(std::to_string(currentFrame));
        currentFrameTime = 0.f;
        currentFrame = 0;
    }
}

void TimeMgr::FrameDisplay(bool active)
{
    if (active)
    {
        frameText.setPosition({ 50.f,50.f });
        frameText.setFillColor(sf::Color::White);
    }
    else
    {
        frameText.setFillColor(sf::Color::Transparent);
    }
}

void TimeMgr::UpdateTime()
{
    sf::Time dt = clock.restart();

    realDeltaTime = deltaTime = dt.asSeconds();
    deltaTime *= timeScale;
    realTime += realDeltaTime;
    time += deltaTime;
}
