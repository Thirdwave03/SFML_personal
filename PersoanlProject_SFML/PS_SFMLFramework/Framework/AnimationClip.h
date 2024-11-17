#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	// PingPong, // ���� �����ư���
};

struct AnimationFrame // �Լ��� �־ Ŭ���� �ִ� ����� ����
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
	AnimationLoopTypes loopType = AnimationLoopTypes::Loop; // �⺻�� Loop�� Ÿ�� ����
	int fps = 30; // �ʴ� ��� ������

	std::vector<AnimationFrame> frames;

	bool loadFromFile(const std::string& filePath);

};