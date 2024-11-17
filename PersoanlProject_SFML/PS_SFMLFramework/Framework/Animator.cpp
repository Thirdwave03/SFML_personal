#include "stdafx.h"
#include "Animator.h"
#include "AnimationClip.h"

void Animator::SetSpeed(float speed)
{
	this->speed = speed;
}

void Animator::AddEvent(const std::string& id, int frame, std::function<void()> action)
{
	auto key = std::pair<std::string, int>(id, frame);
	auto it = events.find(key);
	if (it == events.end())
	{
		events.insert({ key, {id, frame} });
	}
	events[key].actions.push_back(action);
}


void Animator::Update(float dt)
{
	if (!isPlaying)
		return;
	
	accumTime += dt * speed;

	if (std::fabs(accumTime) < frameDuration)
		return;
		

	// fabs ( float 절대값 )
	//if (accumTime < frameDuration)
	//	return;
	
	if (accumTime > frameDuration)
	{
		accumTime -= frameDuration;
		currentFrame++;
	}
	if (accumTime < frameDuration * -1.f)
	{
		accumTime += frameDuration;
		currentFrame--;
	}

	
	//currentFrame++;
	//accumTime = 0.f;

	/*if (currentFrame >= totalFrame && speed > 0)
	{
		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = totalFrame-1;

			break;
		case AnimationLoopTypes::Loop:
			currentFrame = 0;
			break;
		}
	}
	if (currentFrame <= 0 && speed < 0)
	{
		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = 0;

			break;
		case AnimationLoopTypes::Loop:
			currentFrame = totalFrame - 1;
			break;
		}
	}*/

	if (speed > 0 ? currentFrame >= lastFrame : currentFrame <= lastFrame)
	{
		if (!playQueue.empty())
		{
			std::string clipId = playQueue.front();
			Play(clipId, false); // front = 가장 앞놈 리턴
			playQueue.pop();
			return;
		}

		switch (currentClip->loopType)
		{
		case AnimationLoopTypes::Single:
			currentFrame = lastFrame;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = speed > 0 ? 0 : totalFrame - 1;
			break;
		}
	}

	// Map = 키 밸류, Set = 키만 저장
	// 등록된 이벤트가 있는지 검사

	// 언오더드는 해시값 가지고 뭐 함
	// Hash 값, Hash 함수의 출력값이 Hash 값
	// Hash를 만족하려면 특정 조건을 만족하여야 함

	// 가능한 입력값 영역 - 정의역, 가능한 출력값의 영역 - 치역

	// 고정된 출력값의 영역을 가지고 있어야 함 (int 혹은 8바이트 이내 등으로 제한)
	// 필연적으로 중복이 나오는데 (치역 < 정의역) 중복이 잘 안되는것이 Hash 함수

	// 조건 1. 동일한 입력값을 넣으면 동일 출력값이 나와야 함
	// 조건 2. 출력값을 가지고 입력값을 유추 할 수 없어야 함(역함수가 없어야 함)
	// 고정된 사이즈의 정수가 나옴.

	// Hash맵 - 같은 해쉬여도 키,밸류 쌍의 맵을 따로 저장함
	// 복호화불가능한 암호화 정보 ( 복호화 - decrypting )

	// Hash값을 구할 수 없는 상태면 Map, Set 사용 불가능

	SetFrame(currentClip->frames[currentFrame]); 
	// 특정 프레임에 이벤트가 등록되어 있다면 해당 이벤트 실행되도록 함

	//for (int i = 0; i < 3; i++)
	//{
	//	auto find = events.find({ currentClip->id,currentFrame, i});
	//	if (find != events.end())
	//	{
	//		auto& ev = *find;
	//		if (ev.action)
	//		{
	//			ev.action();
	//		}
	//	}
	//}

	auto find = events.find({ currentClip->id, currentFrame });
	if (find != events.end())
	{
		auto& ev = find->second;
		for (auto& action : ev.actions)
		{
			if (action)
			{
				action();
			}
		}
	}
	//find마다 AnimationEvent 객체가 만들어짐에 비효율적임
}

void Animator::Play(AnimationClip* clip, bool clearQueue)
{
	if (clearQueue)
	{
		while (!playQueue.empty())
		{
			playQueue.pop();
		}

	}

	isPlaying = true;
	totalFrame = clip->frames.size();
	lastFrame = speed > 0 ? totalFrame - 1 : 0;

	currentClip = clip;
	currentFrame = speed > 0 ? 0 : totalFrame - 1;

	frameDuration = 1.f / clip->fps;

	accumTime = 0.f;
}

void Animator::Play(const std::string& clipId, bool clearQueue)
{
	Play(&ANI_CLIP_MGR.Get(clipId), clearQueue);
}

void Animator::PlayQueue(const std::string& clipId)
{
	playQueue.push(clipId);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	sprite->setTexture(TEXTURE_MGR.Get(frame.texId));
	sprite->setTextureRect(frame.texCoord);
}
