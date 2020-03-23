#pragma once
#include "SDL.h"
#include "Scene.h"
#include "Rasterizer.h"

class App
{
public:
	explicit App(const unsigned int p_width = 1024, const unsigned int p_height = 768);
	~App();
	void RunLoop();

	SDL_Renderer *GetRenderer() const;
	SDL_Window *GetWindow() const;

private:
	void EventHandler();

private:
	enum class State { RUN, EXIT };

	SDL_Event m_event{};
	unsigned int m_width{ 1024 };
	unsigned int m_height{ 768 };
	SDL_Window *m_mainWindow{ nullptr };
	SDL_Renderer *m_mainRenderer{ nullptr };
	Rasterizer m_rasterizer{ m_mainRenderer, m_mainWindow, m_width, m_height };
	const Uint8 *m_keyboardState = SDL_GetKeyboardState(nullptr);
	Texture m_texture{ m_width, m_height };
	Scene m_scene;
	State m_state;
};