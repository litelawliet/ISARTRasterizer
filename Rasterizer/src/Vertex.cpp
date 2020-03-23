#include "Vertex.h"

Vertex::Vertex()
	: m_position{ 0.0f, 0.0f, 0.0f }, m_normal{ 0.0f, 0.0f, 0.0f }
{}

Vertex::Vertex(const float p_x, const float p_y, const float p_z, const float p_xNormal, const float p_yNormal, const float p_zNormal)
	: m_position{ p_x, p_y, p_z }, m_normal{ p_xNormal, p_yNormal, p_zNormal }
{}

Vertex::Vertex(const Maths::Vector::Vec3 & p_position, const Maths::Vector::Vec3 & p_normal, const Color & p_color)
	: m_position{ p_position }, m_normal{ p_normal }, m_color{ p_color }
{}

Vertex & Vertex::operator=(const Vertex & p_other)
{
	m_position.m_x = p_other.m_position.m_x;
	m_position.m_y = p_other.m_position.m_y;
	m_position.m_z = p_other.m_position.m_z;

	return *this;
}

float Vertex::DotProduct(const Vertex & p_other)
{
	return m_position.m_x * p_other.m_position.m_x + m_position.m_y * p_other.m_position.m_y + m_position.m_z * p_other.m_position.m_z;
}

bool Vertex::operator<(const Vertex & p_other) const
{
	return m_position.m_y < p_other.m_position.m_y;
}

bool Vertex::operator>(const Vertex & p_other) const
{
	return m_position.m_y > p_other.m_position.m_y;
}

bool Vertex::operator==(const Vertex & p_other) const
{
	return m_position.m_y == p_other.m_position.m_y;
}

bool Vertex::operator>=(const Vertex & p_other) const
{
	return m_position.m_y >= p_other.m_position.m_y;
}

bool Vertex::operator<=(const Vertex & p_other) const
{
	return m_position.m_y <= p_other.m_position.m_y;
}

std::string Vertex::ToString() const
{
	return { ("x:" + std::to_string(m_position.m_x) + ", y:" + std::to_string(m_position.m_y) + ", z:" + std::to_string(m_position.m_z)) };
}

Vertex operator-(const Vertex & p_first, const Vertex & p_second)
{
	Vertex tmp;

	tmp.m_position.m_x = p_first.m_position.m_x - p_second.m_position.m_x;
	tmp.m_position.m_y = p_first.m_position.m_y - p_second.m_position.m_y;
	tmp.m_position.m_z = p_first.m_position.m_z - p_second.m_position.m_z;

	return tmp;
}
