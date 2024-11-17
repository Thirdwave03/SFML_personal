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
//	// ���� Ʋ���� ���� ����� �־�� ��
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

// event �Ű������� �޾� hash �� �����ϴ� ���� 
//
//struct AnimationEventHash
//{
//	std::size_t operator()(const AnimationEvent& ev) const // ū unsigned_int�� �����ϸ� ��
//	{
//		//std::hash<std::string> func1;
//		// id �ؽ���, frame �ؽ��� �޾Ƽ� ��Ʈ�������� ��� �ؽ��� ���
//		std::size_t h1 = std::hash<std::string>()(ev.id); // string���� hash�� ���ϴ� ����
//			//���� ��ü , �ӽð�ü ()
//		std::size_t h2 = std::hash<int>()(ev.frame);
//		std::size_t h3 = std::hash<int>()(ev.actionNo);
//		return (h1 ^ (h2 << 1) + ~h3); // X -> True(�ٸ��� true) , << ����Ʈ �������� ��		
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
	// unordered_set ��ü ������ �ؽ� ���� ������ ���������̸� �Ű����� �ϳ���,
	// ������ �ؽ��� ���ϴ� ���͸� �߰� �Ű������� �Ѱ��־�� ��
	// �Ź� �ؽ��� ������ �ؼ� �ϴ� ��ȿ������ ���

	std::unordered_map<std::pair<std::string, int>, AnimationEvent, AnimationEventHash> events;
	std::queue<std::string> playQueue; // Ŭ���� �ִϸ��̼� ���� ť


	AnimationClip* currentClip;
	sf::Sprite* sprite; // �׸��� ��ü

	bool isPlaying = false;
	int currentFrame = 0;  // AnimationClip ������ ������ �ε���
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

