#pragma once

struct Color
{
	unsigned char m_r{ 0 };
	unsigned char m_g{ 0 };
	unsigned char m_b{ 0 };
	unsigned char m_a{ 255 };

	static Color BLACK;
	static Color WHITE;
	static Color RED;
	static Color GREEN;
	static Color BLUE;

	Color() = default;
	Color(unsigned char p_red, unsigned char p_green, unsigned char p_blue, unsigned char p_alpha);
	Color(const Color& p_color) = default;
	~Color() = default;

	Color& operator=(const Color& p_other) = default;
	bool operator!=(const Color& p_other) const;
	bool operator==(const Color& p_other) const;
};
