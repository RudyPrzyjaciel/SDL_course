#include <SDL.h>
#include <stdio.h>
#include <string>

/* Function declarations */
bool init();
bool loadMedia();
void close();

/* Macros & Global Variables */
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 490;

std::string IMAGE_FILE_NAME = "Image.bmp";

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bmpImage = NULL;


int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			SDL_BlitSurface(bmpImage, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	close();

	return 0;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	bmpImage = SDL_LoadBMP(IMAGE_FILE_NAME.c_str());
	if (bmpImage == NULL)
	{
		printf("Unable ro load image %s! SDL_Error: %s\n", IMAGE_FILE_NAME.c_str(), SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	SDL_FreeSurface(bmpImage);
	bmpImage = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}