#include "Scene.h"
#include "Light.h"

Scene::Scene()
{
	m_entities.reserve(8);
	m_lights.emplace_back(0.0f, 0.0f, 0.0f, 0.0f, 0.8f, 0.05f);
}


Scene::~Scene()
{
	m_entities.clear();
}

void Scene::AddEntity(const Entity & p_entity)
{
	m_entities.emplace_back(p_entity);
}

void Scene::SetLights(std::vector<Light>& p_lights)
{
	m_lights = p_lights;
}

std::vector<Entity>& Scene::GetEntities()
{
	return { m_entities };
}

std::vector<Light>& Scene::GetLights()
{
	return { m_lights };
}

void Scene::SetMesh(int p_i, const std::shared_ptr<Mesh>& p_mesh)
{
    if (m_entities.size() > p_i)
    {
        m_entities[p_i].SetMesh(p_mesh);
    }
}

