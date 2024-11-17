#pragma once
#include "AnimationClip.h"

//struct AnimationEvent
//{
//	std::string id;
//	int frame = 0;
//	int actionNo = 0;
//	std::function<void()> action;
//
//	bool operator==(const AnimationEvent& other) const
//	{
//		return (id == other.id) && (frame == other.frame) && (actionNo == other.actionNo);
//	}
//	// 같다 틀리다 기준 만들어 주어야 함
//};

struct AnimationEvent
{
	std::string id;
	int frame = 0;

	std::vector<std::function<void()>> actions;

	bool operator==(const AnimationEvent& other) const
	{
		return (id == other.id) && (frame == other.frame);
	}
};

// event 매개변수로 받아 hash 값 리턴하는 펑터 
//
//struct AnimationEventHash
//{
//	std::size_t operator()(const AnimationEvent& ev) const // 큰 unsigned_int라 생각하면 됨
//	{
//		//std::hash<std::string> func1;
//		// id 해쉬값, frame 해쉬값 받아서 비트연산으로 섞어서 해쉬값 출력
//		std::size_t h1 = std::hash<std::string>()(ev.id); // string형의 hash를 구하는 펑터
//			//펑터 객체 , 임시객체 ()
//		std::size_t h2 = std::hash<int>()(ev.frame);
//		std::size_t h3 = std::hash<int>()(ev.actionNo);
//		return (h1 ^ (h2 << 1) + ~h3); // X -> True(다르면 true) , << 쉬프트 왼쪽으로 밈		
//	}
//};

struct AnimationEventHash
{
	std::size_t operator()(const std::pair<std::string, int>& pair) const
	{
		std::size_t h1 = std::hash<std::string>()(pair.first);
		std::size_t h2 = std::hash<int>()(pair.second);
		return h1 ^ (h2 << 1);
	}
};

class Animator
{
protected:
	//std::unordered_set<AnimationEvent, AnimationEventHash> events;
	// unordered_set 객체 생성시 해쉬 값이 나오는 데이터형이면 매개변수 하나만,
	// 없으면 해쉬값 구하는 펑터를 추가 매개변수로 넘겨주어야 함
	// 매번 해쉬값 만들어야 해서 일단 비효율적인 방식

	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events;
	std::queue<std::string> playQueue; // 클립에 애니메이션 담을 큐


	AnimationClip* currentClip;
	sf::Sprite* sprite; // 그리기 객체

	bool isPlaying = false;
	int currentFrame = 0;  // AnimationClip 프레임 벡터의 인덱스
	int totalFrame = 0;
	int lastFrame = 0;

	float frameDuration = 0.f;
	float accumTime = 0.f;

	float speed = 1.f;

public:
	Animator() {}
	~Animator() = default;
	Animator(const Animator& other) = default;
	Animator& operator=(const Animator& other) = default;

	void SetSpeed(float speed);
	float GetSpeed() { return speed; }

	void SetTarget(sf::Sprite* target) { sprite = target; }

	//void AddEvent(const AnimationEvent& ev)
	//{
	//	if (events.find(ev) != events.end())
	//	{
	//		//error 
	//		return;
	//	}
	//	events.insert(ev);
	//}
	void AddEvent(const std::string& id, int frame, std::function<void()> action);

	void ClearEvent();

	void Update(float dt);

	bool IsPlaying() const { return false; }

	void Play(AnimationClip* clip, bool clearQueue = true);
	void Play(const std::string& clipId, bool clearQueue = true);


	void PlayQueue(const std::string& clipId);

	void Stop();

	void SetFrame(const AnimationFrame& frame);


	std::string GetCurrentClipId() const
	{
		if (currentClip == nullptr)
			return "";
		return currentClip->id;
	}
};

