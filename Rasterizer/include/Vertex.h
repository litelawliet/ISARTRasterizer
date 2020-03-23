#pragma once
#include "Maths/Vec3.h"
#include "Color.h"
#include <string>

using namespace Maths::Vector;

struct Vertex
{
	Vec3 m_position{};
	Vec3 m_normal{};
	Color m_color{};

	Vertex();
	Vertex(const float p_x, const float p_y, const float p_z, const float p_xNormal = 0.0f, const float p_yNormal = 0.0f, const float p_zNormal = 0.0f);
	Vertex(const Vertex& p_other) = default;
	explicit Vertex(const Vec3& p_position, const Vec3& p_normal = Vec3{}, const Color& p_color = Color{});

	Vertex& operator=(const Vertex& p_other);
	float DotProduct(const Vertex& p_other);;
	bool operator<(const Vertex& p_other) const;
	bool operator>(const Vertex& p_other) const;
	bool operator==(const Vertex& p_other) const;
	bool operator>=(const Vertex& p_other) const;
	bool operator<=(const Vertex& p_other) const;
	

	std::string ToString() const;
};
Vertex operator-(const Vertex& p_first, const Vertex& p_second);
