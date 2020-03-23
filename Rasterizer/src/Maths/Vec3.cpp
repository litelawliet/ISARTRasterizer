#include "Maths/Vec3.h"
#include <stdexcept>

using namespace Maths::Vector;

Vec3::Vec3(const float p_value)
	: m_x{ p_value }, m_y{ p_value }, m_z{ p_value }
{}

Vec3::Vec3(const float p_x, const float p_y, const float p_z)
	: m_x{ p_x }, m_y{ p_y }, m_z{ p_z }
{}

Vec3 Vec3::operator+(const Vec3 & p_other) const
{
	return { Vec3{m_x + p_other.m_x, m_y + p_other.m_y, m_z + p_other.m_z} };
}

Vec3 Vec3::operator*(const float p_scalar) const
{
	return { Vec3{m_x * p_scalar, m_y * p_scalar, m_z * p_scalar} };
}

Vec3 Vec3::operator-(const Vec3 & p_other) const
{
	return { Vec3{ p_other.m_x - m_x, p_other.m_y - m_y, p_other.m_z - m_z } };
}

Vec3& Vec3::Centered()
{
	m_x += 512.0f;
	m_y += 384.0f;
	m_z += 0.0f;

	return *this;
}

float Vec3::operator[](const unsigned int p_index) const
{
	switch (p_index)
	{
	case 0:
		return m_x;
	case 1:
		return m_y;
	case 2:
		return m_z;
	default:
		return 0.0f;
	}
}

float Vec3::operator[](const std::string & p_index) const
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

	return 0.0f;
}

float & Vec3::operator[](const unsigned int p_index)
{
	switch (p_index)
	{
	case 0:
		return { m_x };
	case 1:
		return { m_y };
	case 2:
		return { m_z };
	default:
		throw std::out_of_range("Index out of range");
	}
}

float & Vec3::operator[](const std::string & p_index)
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

	throw std::out_of_range("Index out of range");
}


float Vec3::GetDotProduct(const Vec3& p_firstVector, const Vec3& p_secondVector)
{
	return p_firstVector.m_x * p_secondVector.m_x + p_firstVector.m_y * p_secondVector.m_y + p_firstVector.m_z * p_secondVector.m_z;
}

Vec3 Vec3::GetCrossProduct(const Vec3 & p_firstVector, const Vec3 & p_secondVector)
{
	return { Vec3{ (p_firstVector.m_y * p_secondVector.m_z - p_firstVector.m_z * p_secondVector.m_y), -(p_firstVector.m_x * p_secondVector.m_z - p_firstVector.m_z * p_secondVector.m_x), (p_firstVector.m_x * p_secondVector.m_y - p_firstVector.m_y * p_secondVector.m_x) } };
}

Vec3 Vec3::GetSubstractsVector(const Vec3 & p_firstVector, const Vec3 & p_secondVector)
{
	return { Vec3{ p_secondVector.m_x - p_firstVector.m_x, p_secondVector.m_y - p_firstVector.m_y, p_secondVector.m_z - p_firstVector.m_z } };
}

float Vec3::GetMagnitude() const
{
	return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

void Vec3::Normalize()
{
	const auto magnitude = GetMagnitude();

	if (magnitude != 0)
	{
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

Vec3 Vec3::Normalize() const
{
	const auto magnitude = GetMagnitude();

	return { m_x / magnitude, m_y / magnitude, m_z / magnitude };
}

std::string Vec3::ToString() const
{
	return { "X: " + std::to_string(m_x) + ", Y: " + std::to_string(m_y) + ", Z: " + std::to_string(m_z) };
}

Vec3 Vec3::centeredVector{ 512.0f, 384.0f, 0.0f };