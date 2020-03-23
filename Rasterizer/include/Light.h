#pragma once

#include "Maths/Vec3.h"
#include "Maths/Vec4.h"
#include "Color.h"
#include "Vertex.h"

using namespace Maths::Vector;

class Light
{
public:
	explicit Light(const Vec3 p_position = Vec3{ 0.0f, 0.0f, 0.0f }, const float p_ambient = 0, const float p_diffuse = 0, const float p_specular = 0);
	explicit Light(const float p_x = 0.0f, const float p_y = 0.0f, const float p_z = 0.0f, const float p_ambient = 0, const float p_diffuse = 0, const float p_specular = 0);

	Vec3& GetPosition();
	float GetAmbientComponent() const;
	float GetDiffuseComponent() const;
	float GetSpecularComponent() const;

	void SetPosition(const Vec3& p_position);
	void SetPosition(const float p_x = 0, const float p_y = 0, const float p_z = 0);

	void SetAmbientComponent(const float p_value);
	void SetDiffuseComponent(const float p_value);
	void SetSpecularComponent(const float p_value);


	Color CalculateColor(const Color p_color,const Vec3 p_surface, Vec4 p_vertex);

private:
	Vec3 m_position{ 0.0f, 0.0f, 0.0f };
	float m_ambientComponent{ 0.0f };
	float m_diffuseComponent{ 0.0f };
	float m_specularComponent{ 0.0f };

	Vec3 GetLightReflection(Vec3 p_v0, Vec3 p_v1);
};