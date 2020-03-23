#include "Light.h"
#include "Color.h"
#include "Vertex.h"
#include "Maths/Vec4.h"
#include <iostream>
#include <algorithm>

using namespace Maths::Vector;

//ADD LIGHTING HERE EVENTUALLY

Light::Light(const Maths::Vector::Vec3 p_position, const float p_ambient, const float p_diffuse, const float p_specular)
	: m_position{ p_position }, m_ambientComponent{ p_ambient }, m_diffuseComponent{ p_diffuse }, m_specularComponent{ p_specular }
{}

Light::Light(const float p_x, const float p_y, const float p_z, const float p_ambient, const float p_diffuse, const float p_specular)
	: m_position{ p_x, p_y, p_z }, m_ambientComponent{ p_ambient }, m_diffuseComponent{ p_diffuse }, m_specularComponent{ p_specular }
{}

Vec3& Light::GetPosition()
{
	return { m_position };
}

float Light::GetAmbientComponent() const
{
	return m_ambientComponent;
}

float Light::GetDiffuseComponent() const
{
	return m_diffuseComponent;
}

float Light::GetSpecularComponent() const
{
	return m_specularComponent;
}

void Light::SetPosition(const Vec3 & p_position)
{
	m_position = p_position;
}

void Light::SetPosition(const float p_x, const float p_y, const float p_z)
{
	m_position.m_x = p_x;
	m_position.m_y = p_x;
	m_position.m_z = p_z;
}

void Light::SetAmbientComponent(const float p_value)
{
	m_ambientComponent = p_value;
}

void Light::SetDiffuseComponent(const float p_value)
{
	m_diffuseComponent = p_value;
}

void Light::SetSpecularComponent(const float p_value)
{
	m_specularComponent = p_value;
}

Color Light::CalculateColor(const Color p_color, const Vec3 p_surface, Vec4 p_vertex)
{
	Vec3 normalSurface = p_surface;
	//normalSurface.Normalize();

	Vec3 homogenizedVec = Vec3{ p_vertex.m_x / p_vertex.m_w, p_vertex.m_y / p_vertex.m_w, p_vertex.m_z / p_vertex.m_w };

	Vec3 lightPosNormal = m_position - homogenizedVec;
	lightPosNormal.Normalize();
	
	Vec3 reflectedLightVector = GetLightReflection(lightPosNormal, normalSurface);

	float specAngle = std::max(Vec3::GetDotProduct(reflectedLightVector, homogenizedVec), 0.0f);
	float lambertian = std::max(Vec3::GetDotProduct(normalSurface, lightPosNormal), 0.0f);
	float specular = std::pow(specAngle, 1.0);

	float r = (m_ambientComponent * p_color.m_r) + (m_diffuseComponent * lambertian * p_color.m_r) + (m_specularComponent * specular * p_color.m_r);
	float g = (m_ambientComponent * p_color.m_g) + (m_diffuseComponent * lambertian * p_color.m_g) + (m_specularComponent * specular * p_color.m_g);
	float b = (m_ambientComponent * p_color.m_b) + (m_diffuseComponent * lambertian * p_color.m_b) + (m_specularComponent * specular * p_color.m_b);


	return { Color { static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), p_color.m_a} };
}

Vec3 Light::GetLightReflection(Vec3 p_v0, Vec3 p_v1)
{
	Vec3 negatedP0 = p_v0 * -1;
	float dotProductResult = Vec3::GetDotProduct(negatedP0, p_v1);

	return { negatedP0 - (p_v1 * (2 * dotProductResult)) };
}