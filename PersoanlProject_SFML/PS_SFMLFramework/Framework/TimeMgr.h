#pragma once

class TimeMgr : public Singleton<TimeMgr>
{
	friend Singleton<TimeMgr>;
protected:
	TimeMgr() = default;
	virtual ~TimeMgr() = default;

	TimeMgr(const TimeMgr& other) = delete;
	TimeMgr& operator=(const TimeMgr& other) = delete;

	sf::Clock clock;
	float timeScale = 1.f;

	float time = 0.f;
	float deltaTime = 0.f;

	float realTime = 0.f;
	float realDeltaTime = 0.f;

	sf::Text		frameText;
	unsigned int	currentFrame;
	float			currentFrameTime;

	bool frameDisplayActive = true;

public:
	void Init();

	float GetTime() const { return time; }
	float GetDeltaTime() const { return deltaTime; }
	float GetRealTime() const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }

	void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }
	float GetTimeScale() const { return timeScale; }

	void FrameCheck();
	void FrameDisplay(bool active);

	void UpdateTime();

	sf::Text GetFrameText() { return frameText; }
};

#define TIME_MGR (TimeMgr::Instance())