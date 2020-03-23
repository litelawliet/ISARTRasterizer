#include "Texture.h"
#include "Color.h"
#include <algorithm>

Texture::Texture(const unsigned int p_x, const unsigned int p_y)
	: m_width{ p_x }, m_height{ p_y }, m_totalPixels{ m_width * m_height }
{
	m_pixels = new Color[m_width * m_height]{};
	m_oldPixels = new Color[m_width * m_height]{ Color::WHITE };
}

void Texture::SetPixelColor(const unsigned int p_col, const unsigned int p_row, const Color & p_color) const
{

	m_pixels[m_width * p_row + p_col] = p_color;
}

void Texture::SetOldPixelColor(const unsigned int p_col, const unsigned int p_row, const Color & p_color) const
{
	m_oldPixels[m_width * p_row + p_col] = p_color;
}

Texture::~Texture()
{
	delete[] m_pixels;
	delete[] m_oldPixels;
}

unsigned int Texture::GetWidth() const
{
	return m_width;
}

unsigned int Texture::GetHeight() const
{
	return m_height;
}

Color * Texture::GetPixels() const
{
	return m_pixels;
}

Color * Texture::GetOldPixels() const
{
	return m_oldPixels;
}

void Texture::ResetColors() const
{
	std::fill_n(m_pixels, m_totalPixels, Color::BLACK);
}
