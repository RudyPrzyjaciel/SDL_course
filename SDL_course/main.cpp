#include <SDL.h>
#include <stdio.h>
#include <string>

/* Function declarations */
bool init();
void mainApplicationLoop();
bool loadMedia();
void close();

/* Macros & Global Variables */
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 490;

bool quitApplication = false;

std::string IMAGE_FILE_NAME = "Image.bmp";

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* bmpImage = NULL;
SDL_Event event;

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
			mainApplicationLoop();
		}
	}

	close();

	return 0;
}

void mainApplicationLoop()
{
	while (!quitApplication)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quitApplication = true;
				printf("EventHandler: quitApplication = true!\n");
			}
		}

		SDL_BlitSurface(bmpImage, NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}
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

	printf("Init: Success!\n");
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

	printf("LoadData: Success!\n");
	return success;
}

void close()
{
	SDL_FreeSurface(bmpImage);
	bmpImage = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	printf("Close: Success!\n");
}