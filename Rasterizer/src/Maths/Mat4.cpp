#include "Maths/Mat4.h"

using namespace Maths::Matrix;
using namespace Maths::Vector;

Mat4::Mat4(const float p_value)
{
	for (auto& i : m_matrix)
	{
		for (auto& j : i)
		{
			j = p_value;
		}
	}
}

Mat4::Mat4(const Mat4 & p_other)
{
	memcpy(m_matrix, p_other.m_matrix, sizeof(m_matrix));
}

Mat4 Mat4::operator*(const Mat4 & p_other) const
{
	Mat4 tmp{ 0.0f };
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				tmp.m_matrix[i][j] += this->m_matrix[i][k] * p_other.m_matrix[k][j];
			}
		}
	}

	return { tmp };
}

Vec4 Mat4::operator*(const Vec4 & p_other)
{
	Vec4 tmp;

	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			tmp[i] += m_matrix[i][j] * p_other[j];
		}
	}

	return { tmp };
}

Mat4 Mat4::CreateTransformMatrix(const Vec3 & p_rotation, const Vec3 & p_position, const Vec3 & p_scale)
{
	auto transform = CreateTranslationMatrix(p_position) * CreateYRotationMatrix(p_rotation.m_y * 3.1415926535f / 180.0f) * CreateXRotationMatrix(p_rotation.m_x * 3.1415926535f / 180.0f) * CreateZRotationMatrix(p_rotation.m_z * 3.1415926535f / 180.0f) * CreateScaleMatrix(p_scale);

	return transform;
}

Mat4 Mat4::CreateTranslationMatrix(const Vec3 & p_translation)
{
	Mat4 tmp{ 0.0f };

	// column-major matrix
	tmp.m_matrix[0][3] = p_translation.m_x;
	tmp.m_matrix[1][3] = p_translation.m_y;
	tmp.m_matrix[2][3] = p_translation.m_z;

	tmp.m_matrix[0][0] = 1.0f;
	tmp.m_matrix[1][1] = 1.0f;
	tmp.m_matrix[2][2] = 1.0f;
	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}

Mat4 Mat4::CreateScaleMatrix(const Vec3 & p_scale)
{
	Mat4 tmp{ 0.0f };

	tmp.m_matrix[0][0] = p_scale.m_x;
	tmp.m_matrix[1][1] = p_scale.m_y;
	tmp.m_matrix[2][2] = p_scale.m_z;

	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}

Mat4 Mat4::CreateRotationMatrix(const float p_angle, const Vec3 & p_rotation)
{
	Mat4 tmp{ 0.0f };

	const auto c = cosf(p_angle * 3.1415926535f / 180.0f);
	const auto s = sinf(p_angle * 3.1415926535f / 180.0f);

	tmp.m_matrix[0][0] = p_rotation.m_x * p_rotation.m_x * (1 - c) + c;
	tmp.m_matrix[1][0] = p_rotation.m_x * p_rotation.m_y * (1 - c) + p_rotation.m_z * s;
	tmp.m_matrix[2][0] = p_rotation.m_x * p_rotation.m_z * (1 - c) - p_rotation.m_y * s;

	tmp.m_matrix[0][1] = p_rotation.m_x * p_rotation.m_y * (1 - c) - p_rotation.m_z * s;
	tmp.m_matrix[1][1] = p_rotation.m_y * p_rotation.m_y * (1 - c) + c;
	tmp.m_matrix[2][1] = p_rotation.m_y * p_rotation.m_z * (1 - c) + p_rotation.m_x * s;

	tmp.m_matrix[0][2] = p_rotation.m_x * p_rotation.m_z * (1 - c) + p_rotation.m_y * s;
	tmp.m_matrix[1][2] = p_rotation.m_y * p_rotation.m_z * (1 - c) - p_rotation.m_x * s;
	tmp.m_matrix[2][2] = p_rotation.m_z * p_rotation.m_z * (1 - c) + c;

	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}

Mat4 Mat4::CreateXRotationMatrix(const float p_angle)
{
	Mat4 tmp{ 0.0f };

	const auto cosine = cosf(p_angle);
	const auto sinus = sinf(p_angle);

	tmp.m_matrix[0][0] = 1.0f;
	tmp.m_matrix[1][1] = cosine;
	tmp.m_matrix[1][2] = -sinus;
	tmp.m_matrix[2][1] = sinus;
	tmp.m_matrix[2][2] = cosine;
	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}

Mat4 Mat4::CreateYRotationMatrix(const float p_angle)
{
	Mat4 tmp{ 0.0f };

	const auto cosine = cosf(p_angle);
	const auto sinus = sinf(p_angle);

	tmp.m_matrix[0][0] = cosine;
	tmp.m_matrix[0][2] = sinus;
	tmp.m_matrix[1][1] = 1.0f;
	tmp.m_matrix[2][0] = -sinus;
	tmp.m_matrix[2][2] = cosine;
	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}

Mat4 Mat4::CreateZRotationMatrix(const float p_angle)
{
	Mat4 tmp{ 0.0f };

	const auto cosine = cosf(p_angle);
	const auto sinus = sinf(p_angle);

	tmp.m_matrix[0][0] = cosine;
	tmp.m_matrix[0][1] = -sinus;
	tmp.m_matrix[1][0] = sinus;
	tmp.m_matrix[1][1] = cosine;
	tmp.m_matrix[2][2] = 1.0f;
	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}

Mat4 Mat4::CreateIdentityMatrix()
{
	Mat4 tmp{ 0.0f };

	tmp.m_matrix[0][0] = 1.0f;
	tmp.m_matrix[1][1] = 1.0f;
	tmp.m_matrix[2][2] = 1.0f;
	tmp.m_matrix[3][3] = 1.0f;

	return { tmp };
}
