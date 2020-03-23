#include "Color.h"

Color Color::BLACK{ 0, 0, 0, 255 };
Color Color::WHITE{ 255, 255, 255, 255 };
Color Color::RED{ 255, 0, 0, 255 };
Color Color::GREEN{ 0, 255, 0, 255 };
Color Color::BLUE{ 0, 0, 255, 255 };

Color::Color(const unsigned char p_red, const unsigned char p_green, const unsigned char p_blue, const unsigned char p_alpha)
	: m_r{ p_red }, m_g{ p_green }, m_b{ p_blue }, m_a{ p_alpha }
{}

bool Color::operator!=(const Color & p_other) const
{
	return m_b != p_other.m_b || m_g != p_other.m_g || m_r != p_other.m_r || m_a != p_other.m_a;
}

bool Color::operator==(const Color & p_other) const
{
	return m_b == p_other.m_b && m_g == p_other.m_g && m_r == p_other.m_r && m_a == p_other.m_a;
}
