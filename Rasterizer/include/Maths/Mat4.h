#pragma once
#include "Vec3.h"
#include "Vec4.h"

using namespace Maths::Vector;

namespace Maths::Matrix
{
	class Mat4
	{
	public:
		Mat4() = default;
		explicit Mat4(float p_value);
		Mat4(const Mat4& p_other);
		~Mat4() = default;

		Mat4 operator*(const Mat4& p_other) const;
		Vec4 operator*(const Vector::Vec4 & p_other);

		static Mat4 CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale);

		static Mat4 CreateTranslationMatrix(const Vec3& p_translation);

		static Mat4 CreateScaleMatrix(const Vec3& p_scale);

		static Mat4 CreateRotationMatrix(float p_angle, const Vec3& p_rotation);

		static Mat4 CreateXRotationMatrix(float p_angle);
		static Mat4 CreateYRotationMatrix(float p_angle);
		static Mat4 CreateZRotationMatrix(float p_angle);

		static Mat4 CreateIdentityMatrix();

		float m_matrix[4][4]{ {0.0f} };
	};
}