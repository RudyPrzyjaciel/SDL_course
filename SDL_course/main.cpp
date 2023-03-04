#include <SDL.h>
#include <stdio.h>
#include <string>

//------FUNCTION-DECLARATIONS------------//
bool init();
void mainApplicationLoop();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);



//------MACROS-&-GLOBAL-VARIABLES-------//
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 490;

bool quitApplication = false;

std::string IMAGE_FILE_NAME = "Image.bmp";

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_ESCAPE,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentSurface = NULL;
//SDL_Surface* bmpImage = NULL;
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
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
			currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
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
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
					printf("event.key: UP pressed!\n");
					break;

				case SDLK_DOWN:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					printf("event.key: DOWN pressed!\n");
					break;

				case SDLK_LEFT:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					printf("event.key: LEFT pressed!\n");
					break;

				case SDLK_RIGHT:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					printf("event.key: RIGHT pressed!\n");
					break;

				case SDLK_ESCAPE:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_ESCAPE];
					printf("event.key: ESCAPE pressed!\n");
					quitApplication = true;
					printf("event.key: quitApplication = true!\n");
					break;

				default:
					currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					printf("event.key: unhandled pressed!\n");
					break;
				}
			}
		}

		SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
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

	printf("Init: %s", success ? "sucess" : "failure");
	return success;
}

bool loadMedia()
{
	bool success = true;

	keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");	
	if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}
	keyPressSurfaces[KEY_PRESS_SURFACE_ESCAPE] = loadSurface("escape.bmp");
	if (keyPressSurfaces[KEY_PRESS_SURFACE_ESCAPE] == NULL)
	{
		printf("Failed to load escape image!\n");
		success = false;
	}

	printf("LoadData: %s!\n", success ? "success" : "failure");
	return success;
}

void close()
{
	SDL_FreeSurface(currentSurface);
	currentSurface = NULL;

	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	printf("Close: Success!\n");
}


SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s",path.c_str() , SDL_GetError());
	}
	return loadedSurface;
}