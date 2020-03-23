#include "Entity.h"
#include "Maths/Mat4.h"

using namespace Maths::Vector;

Entity::Entity()
	: m_mesh{ nullptr }
{
	m_transformation = Mat4::CreateTransformMatrix(Vec3{ 0.0f, 0.0f, 0.0f }, Vec3{ 1.0f, 1.0f, 1.0f }, Vec3{ 1.0f, 1.0f, 1.0f });
}

Entity::Entity(const Mat4& p_transformation, Mesh* p_mesh)
	: m_mesh{ p_mesh }, m_transformation{ p_transformation }
{
}

std::shared_ptr<Mesh>& Entity::GetMesh()
{
	return m_mesh;
}

const Mat4& Entity::GetTransformation() const
{
	return { m_transformation };
}

void Entity::SetMesh(const std::shared_ptr<Mesh>& p_mesh)
{
	m_mesh = p_mesh;
}

void Entity::SetTransformation(const Mat4& p_transformation)
{
	m_transformation = p_transformation;
}



