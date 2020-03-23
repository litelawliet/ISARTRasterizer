#pragma once


#include "Mesh.h"
#include "Maths/Mat4.h"

using namespace Maths::Matrix;

class Entity
{
public:
	Entity();
	Entity(const Mat4& p_transformation, Mesh* p_mesh = nullptr);
	~Entity() = default;

	std::shared_ptr<Mesh>& GetMesh();
	const Mat4& GetTransformation() const;
	void SetMesh(const std::shared_ptr<Mesh>& p_mesh);
	void SetTransformation(const Mat4& p_transformation);

private:
	std::shared_ptr<Mesh> m_mesh;
	Mat4  m_transformation;
};