#include <iostream>
#include <SDL.h>
#include "App.h"

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL initialization failed.\nSDL Error: " << SDL_GetError();
		return EXIT_FAILURE;
	}
	else
	{
		App Rasterizer{ 1024, 768 };
		Rasterizer.RunLoop();
	}

	return EXIT_SUCCESS;
}