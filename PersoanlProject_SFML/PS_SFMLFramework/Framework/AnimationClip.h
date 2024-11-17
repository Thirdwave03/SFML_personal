#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	// PingPong, // 방향 번갈아가며
};

struct AnimationFrame // 함수를 넣어서 클립에 넣는 방법이 있음
{
	std::string texId;
	sf::IntRect texCoord;
	bool flipX;

	AnimationFrame() {}
	AnimationFrame(const std::string& texId, const sf::IntRect& texCoord)
		: texId(texId), texCoord(texCoord), flipX(flipX) {}
};

struct AnimationClip
{
	std::string id;
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop; // 기본값 Loop로 타입 저장
	int fps = 30; // 초당 재생 프레임

	std::vector<AnimationFrame> frames;

	bool loadFromFile(const std::string& filePath);

};