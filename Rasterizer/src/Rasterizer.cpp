#include "Rasterizer.h"

#include "Maths/Vec3.h"
#include "Maths/Vec4.h"
#include "Light.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>


using namespace Maths::Vector;

Rasterizer::Rasterizer(SDL_Renderer * p_renderer, SDL_Window * p_window, const unsigned int p_width, const unsigned int p_height)
	: m_renderer{ p_renderer }, m_window{ p_window }, m_width{ p_width }, m_height{ p_height }, m_totalPixels{ m_width * m_height }
{
	m_depthBuffer = new double[m_width * m_height]{};
}

Rasterizer::~Rasterizer()
{
	delete[] m_depthBuffer;
}

void Rasterizer::RenderScene(Scene * p_scene, Texture * p_targetTexture)
{
#if BENCHMARK
	m_tmr.reset();
#endif

	if (p_targetTexture != nullptr)
	{
		m_texture = p_targetTexture;

		m_texture->ResetColors();
	}

	if (m_scene != nullptr)
	{
		m_scene = p_scene;

		ResetBuffer();
        size_t i = -1;
		constexpr auto NB_POINTS_BY_TRIANGLE = 3;
        for (auto& entity: m_scene->GetEntities())
		//for (size_t i = 0; i < m_scene->GetEntities().size(); ++i)
		{
            ++i;
			//Entity entity = m_scene->GetEntities()[i];
			Mat4 transformation = entity.GetTransformation();
			std::shared_ptr<Mesh> mesh = entity.GetMesh();

			if (mesh != nullptr)
			{
				// Draw pixels
				Vec4 transformedVertex[NB_POINTS_BY_TRIANGLE];
				Vertex triangleVertices[NB_POINTS_BY_TRIANGLE];

				for (size_t j = 0; j < mesh->m_indices.size() - 2; j += 3)
				{
					for (unsigned int k = 0; k < NB_POINTS_BY_TRIANGLE; ++k)
					{
						transformedVertex[k] = transformation * Vec4{ mesh->m_vertices[mesh->m_indices[j + k]].m_position };
						// Scale...
						transformedVertex[k] = Mat4::CreateRotationMatrix(m_angle, Vec3{ 1.0f, 0.0f, 0.0f }) * Mat4::CreateRotationMatrix(m_angle, Vec3{ 0.0f, 0.0f, 1.0f }) * Mat4::CreateRotationMatrix(m_angle, Vec3{ 0.0f, 1.0f, 0.0f }) * transformedVertex[k];
						//transformedVertex[k] = Mat4::CreateZRotationMatrix(0.0f) * Mat4::CreateXRotationMatrix(m_angle) * Mat4::CreateYRotationMatrix(m_angle) * transformedVertex[k];
						transformedVertex[k] = Mat4::CreateTranslationMatrix(Vec3{ i % 2 == 0 ? -1.0f : 1.0f, 0.0f, 2.0f }) * transformedVertex[k];
						//transformedVertex[k] = Mat4::CreateTransformMatrix(Vec3{ 82.0f, 96.0f, 0.0f }, Vec3{ i % 2 == 0 ? -2.5f : 2.5f, 0.0f, 2.0f } , Vec3{ 1.0f, 1.0f, 1.0f }) * Vec4 { mesh->vertices[mesh->indices[j + k]].position };

						//transformedVertex[k].Homogenize();
						//transformedVertex[k] = Mat4::CreateRotationMatrix(0, Vec3{ 1.0f, 1.0f, 0.0f }) * transformedVertex[k];
						triangleVertices[k] = Vertex{ (transformedVertex[k].m_x / 5.0f + 1.0f) * 0.5f * m_width, m_height - (transformedVertex[k].m_y / 5.0f + 1.0f) * 0.5f * m_height , transformedVertex[k].m_z };
					}

					// call the drawTriangle function IF in screen, some changes have to be done WHEN camera will be added
					if (IsTriangleOnScreenSpace(triangleVertices))
					{
						// backface culling
						// Plane equation of 3 vetices
						//std::cout << triangleVertices[0].ToString() << '\n';
						auto u{ Vec3::GetSubstractsVector(triangleVertices[0].m_position, triangleVertices[1].m_position) };
						//std::cout << u.ToString() << '\n';
						auto v{ Vec3::GetSubstractsVector(triangleVertices[0].m_position, triangleVertices[2].m_position) };
						const auto normalVector = Vec3::GetCrossProduct(u, v);
						//std::cout << normalVector.ToString();
						if (normalVector.m_z > 0)
						{
							DrawTriangle(triangleVertices[0], triangleVertices[1], triangleVertices[2], transformedVertex[0]);
						}
					}
				}
			}
		}
	}
	DrawTexture();

#if BENCHMARK
	const auto frameDuration = m_tmr.elapsed();
	const auto instantFps = 1.00 / frameDuration;

	m_addedDurationOverASecond += frameDuration;

	if (m_addedDurationOverASecond > 1.00)
	{
		++m_numberOfSecondsLast;

		m_queuedFps += instantFps;

		if (m_numberOfSecondsLast == 2)
		{
			m_averageFps = m_queuedFps / m_numberOfSecondsLast;
			m_queuedFps = 0.0;
			m_numberOfSecondsLast = 0;
		}
		m_addedDurationOverASecond = 0.00;
	}
	std::cout << "Frame duration: " << m_tmr.elapsed()
		<< " sec\nInstantly FPS: " << round(instantFps)
		<< "\n-->Average FPS: " << round(m_averageFps) << "\n------------------------------\n";
#endif

	m_angle -= 2.0f;
}

void Rasterizer::ResetBuffer() const
{
	std::fill_n(m_depthBuffer, m_totalPixels, std::numeric_limits<double>::infinity());
}

void Rasterizer::SetScene(Scene * p_scene)
{
	m_scene = p_scene;
}

void Rasterizer::SetTexture(Texture * p_texture)
{
	m_texture = p_texture;
}

void Rasterizer::SetRenderer(SDL_Renderer * p_renderer)
{
	m_renderer = p_renderer;
}

void Rasterizer::SetWindow(SDL_Window * p_window)
{
	m_window = p_window;
}

void Rasterizer::SetMode(const RenderingMode p_mode)
{
	m_mode = p_mode;
}

Rasterizer::RenderingMode Rasterizer::GetMode() const
{
	return m_mode;
}

void Rasterizer::DrawTriangle(Vertex p_v1, Vertex p_v2, Vertex p_v3, Vec4 p_vec4_transform)
{
	//SortVerticesAscendingByY(&p_v1, &p_v2, &p_v3);

	switch (m_mode)
	{
	case RenderingMode::RED:
		m_standardColor = Color::RED;
		break;
	case RenderingMode::GREEN:
		m_standardColor = Color::GREEN;
		break;
	case RenderingMode::BLUE:
		m_standardColor = Color::BLUE;
		break;
	default:
	    break;
	}

	/* check for trivial case of bottom-flat triangle
	//if (p_v2.m_position.m_y == p_v3.m_position.m_y)
	{
		FillBottomFlatTriangle(p_v1, p_v2, p_v3, p_vec4_transform);
	}	// check for trivial case of top-flat triangle
	else if (p_v1.m_position.m_y == p_v2.m_position.m_y)
	{
		FillTopFlatTriangle(p_v1, p_v2, p_v3, p_vec4_transform);
	}
	else
	{
		// general case - split the triangle in a top flat and bottom-flat one
		const Vertex v4{
			p_v1.m_position.m_x + (static_cast<float>(p_v2.m_position.m_y - p_v1.m_position.m_y) / static_cast<float>(p_v3.m_position.m_y - p_v1.m_position.m_y)) * (p_v3.m_position.m_x - p_v1.m_position.m_x), p_v2.m_position.m_y, 0.0f };
		FillBottomFlatTriangle(p_v1, p_v2, v4, p_vec4_transform);
		FillTopFlatTriangle(p_v2, v4, p_v3, p_vec4_transform);
	}*/


	/* get the bounding box of the triangle */
	int maxX = static_cast<int>(std::max(p_v1.m_position.m_x, std::max(p_v2.m_position.m_x, p_v3.m_position.m_x)));
	int minX = static_cast<int>(std::min(p_v1.m_position.m_x, std::min(p_v2.m_position.m_x, p_v3.m_position.m_x)));
	int maxY = static_cast<int>(std::max(p_v1.m_position.m_y, std::max(p_v2.m_position.m_y, p_v3.m_position.m_y)));
	int minY = static_cast<int>(std::min(p_v1.m_position.m_y, std::min(p_v2.m_position.m_y, p_v3.m_position.m_y)));

	Vertex v0{ p_v3 - p_v1 };
	Vertex v1{ p_v2 - p_v1 };

	for (int x = minX; x <= maxX; ++x)
	{
		for (int y = minY; y <= maxY; ++y)
		{
			Vertex p{ static_cast<float>(x), static_cast<float>(y), 1.0f };
			Vertex v2{ p - p_v1 };

			// Color weight
			float w1 = 0.0f;
			float w2 = 0.0f;
			float w3 = 0.0f;
			double zIndex = std::numeric_limits<double>::infinity();

			if (IsPixelOnScreen(x, y))
			{
				//std::cout << "allo ???\n";

				// Calculate the color of the current pixel (x;y) using Barycentric coordinates :
				w1 = ((p_v2.m_position.m_y - p_v3.m_position.m_y) * (x - p_v3.m_position.m_x) + (p_v3.m_position.m_x - p_v2.m_position.m_x) * (y - p_v3.m_position.m_y))
					/ ((p_v2.m_position.m_y - p_v3.m_position.m_y) * (p_v1.m_position.m_x - p_v3.m_position.m_x) + (p_v3.m_position.m_x - p_v2.m_position.m_x) * (p_v1.m_position.m_y - p_v3.m_position.m_y));

				w2 = ((p_v3.m_position.m_y - p_v1.m_position.m_y) * (x - p_v3.m_position.m_x) + (p_v1.m_position.m_x - p_v3.m_position.m_x) * (y - p_v3.m_position.m_y))
					/ ((p_v2.m_position.m_y - p_v3.m_position.m_y) * (p_v1.m_position.m_x - p_v3.m_position.m_x) + (p_v3.m_position.m_x - p_v2.m_position.m_x) * (p_v1.m_position.m_y - p_v3.m_position.m_y));

				w3 = 1 - w1 - w2;

				//z_index =  ( (1 / v1.position.z * w1 + 1 / v2.position.z * w2 + 1 / v3.position.z * w3)); // pixel z precise
				zIndex = 1 / (w1 / p_v1.m_position.m_z + w2 / p_v2.m_position.m_z + w3 / p_v3.m_position.m_z); // fce z approximation
																											   //z_index = v1.position.z * w3 + v2.position.z * w1 + v3.position.z * w2;

				if (m_mode == RenderingMode::INTERPOLATED)
				{
					const auto r = static_cast<unsigned char>(ceil((w1 * 100) * 255 / 100));
					const auto g = static_cast<unsigned char>(ceil((w2 * 100) * 255 / 100));
					const auto b = static_cast<unsigned char>(ceil((w3 * 100) * 255 / 100));

					m_standardColor.m_r = r;
					m_standardColor.m_g = g;
					m_standardColor.m_b = b;
					m_standardColor.m_a = 255;
				}

				float dot00 = v0.DotProduct(v0);
				float dot01 = v0.DotProduct(v1);
				float dot02 = v0.DotProduct(v2);
				float dot11 = v1.DotProduct(v1);
				float dot12 = v1.DotProduct(v2);

				float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
				
				float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
				float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
				//std::cout << u << " : " << v << '\n';
				if ((u >= 0.0f) && (v >= 0.0f) && (u + v < 1.0f))
				{
					//std::cout << "allo ???\n";
					// barycentric formula
					if (zIndex < m_depthBuffer[y * m_width + x])
					{
						m_depthBuffer[y * m_width + x] = zIndex;
						m_texture->SetPixelColor(x, y, m_scene->GetLights()[0].CalculateColor(Color{ m_standardColor.m_r, m_standardColor.m_g, m_standardColor.m_b, m_standardColor.m_a }, Vec3{ w1, w2, w3 }, p_vec4_transform));
					}
				}
			}
		}
	}
}

void Rasterizer::SortVerticesAscendingByY(Vertex * p_v1, Vertex * p_v2, Vertex * p_v3) const
{
	std::vector<Vertex> vertex = { *p_v1, *p_v2, *p_v3 };

	std::sort(vertex.begin(), vertex.end());

	*p_v1 = vertex[0];
	*p_v2 = vertex[1];
	*p_v3 = vertex[2];
}

void Rasterizer::DrawTexture() const
{
#if BENCHMARK
	auto nbPixels = 0;
#endif
	const auto currentPixels = m_texture->GetPixels();
	const auto oldPixels = m_texture->GetOldPixels();
	const auto height = m_texture->GetHeight();
	const auto width = m_texture->GetWidth();

	for (unsigned int i = 0, rowOffset, finalIndex; i < height; ++i)
	{
		rowOffset = i * width;
		for (unsigned int j = 0; j < width; ++j)
		{
			finalIndex = rowOffset + j;
			if (currentPixels[finalIndex] != oldPixels[finalIndex])
			{
				SDL_SetRenderDrawColor(m_renderer, currentPixels[finalIndex].m_r, currentPixels[finalIndex].m_g, currentPixels[finalIndex].m_b, currentPixels[finalIndex].m_a);
				SDL_RenderDrawPoint(m_renderer, j, i);
				m_texture->SetOldPixelColor(j, i, currentPixels[finalIndex]);
#if BENCHMARK
				++nbPixels;
#endif

			}
		}
	}
#if BENCHMARK
	std::cout << "Pixels drawn: " << nbPixels << '\n';
#endif

}

bool Rasterizer::IsTriangleOnScreenSpace(Vertex * p_vertices) const
{
	return ((p_vertices[0].m_position.m_x > 0 || p_vertices[1].m_position.m_x > 0 || p_vertices[2].m_position.m_x > 0)
		&& (p_vertices[0].m_position.m_x < m_width || p_vertices[1].m_position.m_x < m_width || p_vertices[2].m_position.m_x < m_width))
		&& ((p_vertices[0].m_position.m_y > 0 || p_vertices[1].m_position.m_y > 0 || p_vertices[2].m_position.m_y > 0)
			&& (p_vertices[0].m_position.m_y < m_height || p_vertices[1].m_position.m_y < m_height || p_vertices[2].m_position.m_y < m_height));
}

bool Rasterizer::IsPixelOnScreen(const unsigned int p_x, const unsigned int p_y) const
{
	return p_x > 0 && p_x < m_width && (p_y > 0 && p_y < m_height);
}