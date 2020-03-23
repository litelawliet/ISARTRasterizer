#include "App.h"
#include "SDL.h"
#include <iostream>
#include <unordered_map>

App::App(const unsigned int p_width, const unsigned int p_height)
	: m_width{ p_width }, m_height{ p_height }, m_state{State::RUN }
{
	SDL_Init(SDL_INIT_VIDEO);

	m_mainWindow = SDL_CreateWindow(
		"Rasterizer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		p_width,
		p_height,
		SDL_WINDOW_OPENGL);

	if (m_mainWindow == nullptr)
	{
		std::cerr << "Could not Create Window\nSDL Error: " << SDL_GetError();
	}

	m_mainRenderer = SDL_CreateRenderer(
		m_mainWindow,
		-1,
		SDL_RENDERER_ACCELERATED);

	if (m_mainRenderer == nullptr)
	{
		std::cerr << "Could Not Create Renderer\nSDL Error: " << SDL_GetError();
	}

	m_scene.AddEntity(Entity{});
	m_scene.AddEntity(Entity{});
    m_scene.SetMesh(0, Mesh::CreateCube());
    m_scene.SetMesh(1, Mesh::CreateSphere(7, 7));
	//m_scene.GetEntities()[0].SetMesh(Mesh::CreateCube());
	//m_scene.GetEntities()[1].SetMesh(Mesh::CreateSphere(7, 7));

	m_rasterizer.SetRenderer(m_mainRenderer);
	m_rasterizer.SetWindow(m_mainWindow);
	m_rasterizer.SetScene(&m_scene);
	m_rasterizer.SetTexture(&m_texture);
}

App::~App()
{
	SDL_DestroyRenderer(m_mainRenderer);
	SDL_DestroyWindow(m_mainWindow);
	SDL_Quit();
}

void App::EventHandler()
{
    std::unordered_map<int, Rasterizer::RenderingMode> modeMap;
    modeMap[SDL_SCANCODE_R] = Rasterizer::RenderingMode::RED;
    modeMap[SDL_SCANCODE_G] = Rasterizer::RenderingMode::GREEN;
    modeMap[SDL_SCANCODE_B] = Rasterizer::RenderingMode::BLUE;
    modeMap[SDL_SCANCODE_D] = Rasterizer::RenderingMode::INTERPOLATED;

	if (m_keyboardState[SDL_SCANCODE_ESCAPE])
	{
		m_state = State::EXIT;
	}

    for (const std::pair<int, Rasterizer::RenderingMode> element: modeMap)
    {
        if (m_keyboardState[element.first])
            m_rasterizer.SetMode(element.second);
    }

	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
		{
			m_state = State::EXIT;
		}
	}
}

void App::RunLoop()
{
	while (m_state == State::RUN)
	{
		SDL_PumpEvents();
		EventHandler();

		m_rasterizer.RenderScene(&m_scene, &m_texture);
		SDL_RenderPresent(m_mainRenderer);
	}
}

SDL_Renderer * App::GetRenderer() const
{
	return m_mainRenderer;
}

SDL_Window * App::GetWindow() const
{
	return m_mainWindow;
}