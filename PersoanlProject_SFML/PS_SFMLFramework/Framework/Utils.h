#pragma once
#include <sstream>

class Utils
{
private:
	static std::mt19937 generator;
	static const float PI;

public:
	static void Init();

	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);
	static float RandomValue();	// 0.0f ~ 1.0f
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static sf::Color RandomColor(bool opaque = true);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable &obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);
	static sf::Vector2f SetOrigin5SQ(sf::Transformable& obj, Origin5SQ preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin5SQ(sf::Shape& obj, Origin5SQ preset);
	static sf::Vector2f SetOrigin5SQ(sf::Text& obj, Origin5SQ preset);
	static sf::Vector2f SetOrigin5SQ(sf::Sprite& obj, Origin5SQ preset);

	static sf::Vector2f SetOrigin5SQOutBound(sf::Transformable& obj, Origin5SQ preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin5SQOutBound(sf::Shape& obj, Origin5SQ preset);
	static sf::Vector2f SetOrigin5SQOutBound(sf::Text& obj, Origin5SQ preset);
	static sf::Vector2f SetOrigin5SQOutBound(sf::Sprite& obj, Origin5SQ preset);

	static sf::Vector2f SetOriginBelowBC(sf::Sprite& obj);

	// Math
	static float Clamp(float value, float min, float max);
	static float Clamp01(float value);

	static float Lerp(float min, float max, float t, bool clamp = true);
	static sf::Vector2f Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp = true);
	static sf::Color Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp = true);

	static float SqrMagnitude(const sf::Vector2f& vec);
	static float Magnitude(const sf::Vector2f& vec);

	static void Normalize(sf::Vector2f& vec);
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
	static float DistanceWithIsoTileRatio(const sf::Vector2f& p1, const sf::Vector2f& p2);

	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);

	static float AngleRadian(const sf::Vector2f& vec);
	static float Angle(const sf::Vector2f& vec);

	static float Dot(const sf::Vector2f& a, const sf::Vector2f& b);

	static float GetPI();

	//�浹 CheckCollision = SAT ��� �浹ó��
	static bool CheckCollision(const sf::RectangleShape& shapeA, const sf::RectangleShape& shapeB);

	static bool PointInTransformBounds(const sf::Transformable& transformable,
		const sf::FloatRect& localBounds, const sf::Vector2f point);

	static std::vector<sf::Vector2f> GetShapePoints(const sf::RectangleShape& shape);
	static std::vector<sf::Vector2f> GetRectanglePointsFromBounds(const sf::FloatRect& localBounds);
	static bool PolygonsIntersect(const std::vector<sf::Vector2f>& polygonA, const sf::Transform& transformA,
		const std::vector<sf::Vector2f>& polygonB, const sf::Transform& transformB);
};

#define Pi (Utils::GetPI())


template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return std::move(out).str();
}