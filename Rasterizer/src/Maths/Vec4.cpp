#include "Maths/Vec4.h"
#include <stdexcept>

using namespace Maths::Vector;

Vec4::Vec4(const float p_x, const float p_y, const float p_z, const float p_w)
	: m_x{ p_x }, m_y{ p_y }, m_z{ p_z }, m_w{ p_w }
{}

Vec4::Vec4(const Vec3 & p_other, const float p_w)
	: m_x{ p_other.m_x }, m_y{ p_other.m_y }, m_z{ p_other.m_z }, m_w{ p_w }
{}

Vec4 Vec4::operator+(const Vec4 & p_other) const
{
	return { Vec4{m_x + p_other.m_x, m_y + p_other.m_y, m_z + p_other.m_z, m_w + p_other.m_w } };
}

Vec4 Vec4::operator*(const float p_scalar) const
{
	return { Vec4{m_x * p_scalar, m_y * p_scalar, m_z * p_scalar, m_w * p_scalar} };
}

Vec4 Vec4::operator-(const Vec4 & p_other) const
{
	return { Vec4{ p_other.m_x - m_x, p_other.m_y - m_y, p_other.m_z - m_z } };
}

float Vec4::operator[](const unsigned int p_index) const
{
	switch (p_index)
	{
	case 0:
		return m_x;
	case 1:
		return m_y;
	case 2:
		return m_z;
	case 3:
		return m_w;
	default:
		return 0.0f;
	}
}

float Vec4::operator[](const std::string & p_index) const
{
	if (p_index == "x")
	{
		return m_x;
	}
	else if (p_index == "y")
	{
		return m_y;
	}
	else if (p_index == "z")
	{
		return m_z;
	}
	else if (p_index == "w")
	{
		return m_w;
	}

	return 0.0f;
}

float & Vec4::operator[](const unsigned int p_index)
{
	switch (p_index)
	{
	case 0:
		return { m_x };
	case 1:
		return { m_y };
	case 2:
		return { m_z };
	case 3:
		return { m_w };
	default:
		throw std::out_of_range("Index out of range");
	}
}

float & Vec4::operator[](const std::string & p_index)
{
	if (p_index == "x")
	{
		return { m_x };
	}
	else if (p_index == "y")
	{
		return { m_y };
	}
	else if (p_index == "z")
	{
		return { m_z };
	}
	else if (p_index == "w")
	{
		return { m_w };
	}

	throw std::out_of_range("Index out of range");
}



float Vec4::GetDotProduct(const Vec4 & p_firstVector, const Vec4 & p_secondVector)
{
	return p_firstVector.m_x * p_secondVector.m_x + p_firstVector.m_y * p_secondVector.m_y + p_firstVector.m_z * p_secondVector.m_z;
}

float Vec4::GetMagnitude() const
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}


void Vec4::Normalize()
{
	const auto magnitude = GetMagnitude();

	if (magnitude != 0)
	{
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

void Vec4::Homogenize()
{
	if (m_w != 0)
	{
		m_x /= m_w;
		m_y /= m_w;
		m_z /= m_w;
		m_w /= m_w;
	}
}

Vertex Vec4::GetVertex() const
{
	return { Vertex{m_x, m_y, m_z} };
}

Vertex Vec4::GetVertex(const Vec4 & p_other)
{
	return { Vertex{ p_other.m_x, p_other.m_y, p_other.m_z } };
}

std::string Vec4::ToString() const
{
	return { "X: " + std::to_string(m_x) + ", Y: " + std::to_string(m_y) + ", Z: " + std::to_string(m_z) + ", W: " + std::to_string(m_w) };
}
