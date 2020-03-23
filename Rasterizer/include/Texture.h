#pragma once
#include "Color.h"

class Texture
{
public:
	Texture(const unsigned int p_x, const unsigned int p_y);
	void SetPixelColor(const unsigned int p_col, const unsigned int p_row, const Color& p_color) const;
	void SetOldPixelColor(const unsigned int p_col, const unsigned int p_row, const Color& p_color) const;

	~Texture();

	unsigned int GetWidth()const;
	unsigned int GetHeight()const;
	Color* GetPixels() const;
	Color* GetOldPixels() const;
	void ResetColors() const;

private:
	Color* m_pixels{ nullptr };
	Color* m_oldPixels{ nullptr };
	unsigned int m_width{ 0 };
	unsigned int m_height{ 0 };
	unsigned int m_totalPixels { 0 };
};