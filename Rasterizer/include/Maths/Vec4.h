#pragma once

#include <string>
#include "Vec3.h"
#include "Vertex.h"

namespace Maths::Vector
{
	class Vec4
	{
	public:
		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };
		float m_w{ 1.0f };

		Vec4() = default;
		Vec4(float p_x, float p_y, float p_z, float p_w = 1.0f);
		explicit Vec4(const Vec3& p_other, float p_w = 1.0f);
		Vec4(const Vec4& p_other) = default;
		~Vec4() = default;


		Vec4 operator+(const Vec4 & p_other) const;
		Vec4 operator*(float p_scalar) const;
		Vec4 operator-(const Vec4 & p_other) const;

		float operator[](unsigned int p_index) const;
		float operator[](const std::string & p_index) const;
		float& operator[](unsigned int p_index);
		float& operator[](const std::string & p_index);

		static float GetDotProduct(const Vec4 & p_firstVector, const Vec4 & p_secondVector);
		float GetMagnitude() const;
		void Normalize();
		void Homogenize();

		Vertex GetVertex() const;
		static Vertex GetVertex(const Vec4 & p_other);

		std::string ToString() const;
	};

}