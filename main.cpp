//
// main.cpp
// 2017-09-21
//

#include <SDL.h>

SDL_Window		*mainWindow = nullptr;
SDL_Renderer	*renderer = nullptr;

//is the game running?
bool running = false;


// Initializes SDL, create a window and a renderer
bool AGInitialize(const char* windowTitle, int xPos, int yPos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false; // could not initialize	
	}
	else
	{
		mainWindow = SDL_CreateWindow(windowTitle, xPos, yPos, width, height, SDL_WINDOW_SHOWN);

		if (mainWindow != nullptr)
		{
			renderer = SDL_CreateRenderer(mainWindow, -1, 0);
		}

		return true;
	}
}


// 
void AGRender()
{
	SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	// wait 10 secs
	SDL_Delay(10000);
}

// entry point
int main(int argc, char **argv)
{
	if (!AGInitialize("agame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600))
	{
		return 1; // initialization failed
	}


	running = true;

	// main loop
	//while (running)
	//{
		AGRender();
	//}


	SDL_Quit();

	return 0;
}
