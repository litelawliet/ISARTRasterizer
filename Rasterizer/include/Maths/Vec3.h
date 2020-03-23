#pragma once

#include <string>

namespace Maths::Vector
{
	class Vec3
	{
	public:
		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };

		Vec3() = default;
		explicit Vec3(float p_value);
		Vec3(float p_x, float p_y, float p_z);
		Vec3(const Vec3& p_other) = default;
		~Vec3() = default;

		Vec3 operator+(const Vec3 & p_other) const;
		Vec3 operator*(float p_scalar) const;
		Vec3 operator-(const Vec3 & p_other) const;

		Vec3& Centered();
		static Vec3 GetCrossProduct(const Vec3& p_firstVector, const Vec3& p_secondVector);
		static Vec3 GetSubstractsVector(const Vec3& p_firstVector, const Vec3& p_secondVector);

		float operator[](unsigned int p_index) const;
		float operator[](const std::string & p_index) const;
		float& operator[](unsigned int p_index);
		float& operator[](const std::string & p_index);

		static float GetDotProduct(const Vec3& p_firstVector, const Vec3& p_secondVector);

		float GetMagnitude() const;
		void Normalize();
		Vec3 Normalize() const;
		std::string ToString() const;

		static Vec3 centeredVector;
	};

}