#pragma once

#include <memory>

#include "Vertex.h"
#include <vector>

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	// For drawing a cube, or sphere, just loop over vertices with index i of for loop
	// and select the index of vertices using indices[i] as index.
	static std::shared_ptr<Mesh> CreateCube();
	static std::shared_ptr<Mesh> CreateSphere(const int p_latitudeCount, const int p_longitudeCount);

	std::vector<Vertex> m_vertices{};
	std::vector<unsigned int> m_indices{};
};