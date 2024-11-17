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
		

	// fabs ( float ���밪 )
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
			Play(clipId, false); // front = ���� �ճ� ����
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

	// Map = Ű ���, Set = Ű�� ����
	// ��ϵ� �̺�Ʈ�� �ִ��� �˻�

	// �������� �ؽð� ������ �� ��
	// Hash ��, Hash �Լ��� ��°��� Hash ��
	// Hash�� �����Ϸ��� Ư�� ������ �����Ͽ��� ��

	// ������ �Է°� ���� - ���ǿ�, ������ ��°��� ���� - ġ��

	// ������ ��°��� ������ ������ �־�� �� (int Ȥ�� 8����Ʈ �̳� ������ ����)
	// �ʿ������� �ߺ��� �����µ� (ġ�� < ���ǿ�) �ߺ��� �� �ȵǴ°��� Hash �Լ�

	// ���� 1. ������ �Է°��� ������ ���� ��°��� ���;� ��
	// ���� 2. ��°��� ������ �Է°��� ���� �� �� ����� ��(���Լ��� ����� ��)
	// ������ �������� ������ ����.

	// Hash�� - ���� �ؽ����� Ű,��� ���� ���� ���� ������
	// ��ȣȭ�Ұ����� ��ȣȭ ���� ( ��ȣȭ - decrypting )

	// Hash���� ���� �� ���� ���¸� Map, Set ��� �Ұ���

	SetFrame(currentClip->frames[currentFrame]); 
	// Ư�� �����ӿ� �̺�Ʈ�� ��ϵǾ� �ִٸ� �ش� �̺�Ʈ ����ǵ��� ��

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
	//find���� AnimationEvent ��ü�� ��������� ��ȿ������
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
