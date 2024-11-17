#include "stdafx.h"
#include "Framework.h"
#include "SpriteGo.h"

void Framework::Init(int width, int height, const std::string& name)
{
    settings.antialiasingLevel = 10;

	window.create(sf::VideoMode(width, height), name);
    Utils::Init();
    SCENE_MGR.Init();
    SOUND_MGR.Init();
    TIME_MGR.Init();
    InputMgr::Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        TIME_MGR.UpdateTime();

        InputMgr::Clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                
            }
            InputMgr::UpdateEvent(event);
        }
        InputMgr::Update(TIME_MGR.GetRealDeltaTime());
        
        SCENE_MGR.Update(TIME_MGR.GetDeltaTime());
        SCENE_MGR.LateUpdate(TIME_MGR.GetDeltaTime());
        SCENE_MGR.FixedUpdate(TIME_MGR.GetDeltaTime());

        TIME_MGR.FrameCheck();

        window.clear();
        SCENE_MGR.Draw(window);
        window.draw(TIME_MGR.GetFrameText());
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
}
