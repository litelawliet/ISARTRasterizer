#pragma once

#include "Entity.h"
#include "Light.h"
#include <vector>


class Scene
{
public:
	Scene();
	~Scene();

	void AddEntity(const Entity& p_entity);
	void SetLights(std::vector<Light>& p_lights);

	std::vector<Entity>& GetEntities();
	std::vector<Light>& GetLights();
    void SetMesh(int p_i, const std::shared_ptr<Mesh>& p_mesh);

private:
	std::vector<Entity> m_entities;
	std::vector<Light> m_lights;
};

