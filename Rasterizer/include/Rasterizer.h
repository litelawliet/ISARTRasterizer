#pragma once
#include "Tools/BenchmarkTool.h"

#include "Scene.h"
#include "Texture.h"
#include "Vertex.h"
#include <SDL.h>

class Rasterizer
{
public:
	enum class RenderingMode
	{
		INTERPOLATED,
		RED,
		GREEN,
		BLUE,
	};

	Rasterizer(SDL_Renderer * p_renderer, SDL_Window * p_window, const unsigned int p_width, const unsigned int p_height);
	~Rasterizer();
	void RenderScene(Scene* p_scene, Texture* p_targetTexture);
	void SetScene(Scene * p_scene);
	void SetTexture(Texture * p_texture);
	void SetRenderer(SDL_Renderer * p_renderer);
	void SetWindow(SDL_Window * p_window);
	void SetMode(RenderingMode p_mode);
	RenderingMode GetMode() const;

private:
#if BENCHMARK
	Timer m_tmr;
	double m_addedDurationOverASecond{ 0.0 };
	double m_averageFps { 0.0 };
	double m_queuedFps { 0.0 };
	unsigned int m_numberOfSecondsLast{ 0 };
#endif
	double* m_depthBuffer{ nullptr };
	Scene * m_scene{ nullptr };
	Texture* m_texture{ nullptr };
	SDL_Renderer * m_renderer{ nullptr };
	SDL_Window * m_window{ nullptr };
	unsigned int m_width{ 0 };
	unsigned int m_height{ 0 };
	unsigned int m_totalPixels{ 0 };
	Color m_standardColor{ Color::WHITE };
	float m_angle{ 0.0f };
	RenderingMode m_mode{ RenderingMode::INTERPOLATED };
	
    void DrawTriangle(Vertex p_v1, Vertex p_v2, Vertex p_v3, const Vec4 p_vec4_transform);
	void SortVerticesAscendingByY(Vertex * p_v1, Vertex * p_v2, Vertex * p_v3) const;

	void DrawTexture() const;

	bool IsTriangleOnScreenSpace(Vertex * p_vertices) const;
	bool IsPixelOnScreen(const unsigned int p_x, const unsigned int p_y) const;
	void ResetBuffer() const;
};
