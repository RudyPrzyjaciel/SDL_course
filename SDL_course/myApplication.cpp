#include "myApplication.h"

bool myApplication::loadMedia()
{
	bool success = true;

	this->keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (this->keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	this->keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (this->keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	this->keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (this->keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	this->keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (this->keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	this->keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (this->keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	this->keyPressSurfaces[KEY_PRESS_SURFACE_ESCAPE] = loadSurface("escape.bmp");
	if (this->keyPressSurfaces[KEY_PRESS_SURFACE_ESCAPE] == NULL)
	{
		printf("Failed to load escape image!\n");
		success = false;
	}

	printf("loadMedia(): %s!\n", success ? "success" : "failure");
	return success;
}

SDL_Surface* myApplication::loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = NULL;
	SDL_Surface* convertedSurface = NULL;

	loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("loadSurface(): Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		convertedSurface = SDL_ConvertSurface(loadedSurface, this->screenSurface->format, 0);
		if (convertedSurface == NULL)
		{
			printf("loadSurface(): Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return convertedSurface;
}

bool myApplication::init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		this->myAppWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (this->myAppWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			this->screenSurface = SDL_GetWindowSurface(this->myAppWindow);
		}
	}
	printf("init(): %s\n", success ? "success" : "fauilure");
	this->loadMedia();
	return success;
}

void myApplication::mainLoop()
{
	bool quitApplication = false;
	this->currentScreenSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	while (!quitApplication)
	{
		while (SDL_PollEvent(&this->event) != 0)
		{
			if (this->event.type == SDL_QUIT)
			{
				printf("mainLoop(): quitApplication = true!\n");
				quitApplication = true;
			}
			else if (this->event.type == SDL_KEYDOWN)
			{
				switch (this->event.key.keysym.sym)
				{
				case SDLK_UP:
					this->currentScreenSurface = this->keyPressSurfaces[KEY_PRESS_SURFACE_UP];
					printf("mainLoop(): UP arrow key press!\n");
					break;
				case SDLK_DOWN:
					this->currentScreenSurface = this->keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					printf("mainLoop(): Down arrow key press!\n");
					break;
				case SDLK_LEFT:
					this->currentScreenSurface = this->keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					printf("mainLoop(): Left arrow key press!\n");
					break;
				case SDLK_RIGHT:
					this->currentScreenSurface = this->keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					printf("mainLoop(): Right arrow key press!\n");
					break;

				case SDLK_ESCAPE:
					this->currentScreenSurface = this->keyPressSurfaces[KEY_PRESS_SURFACE_ESCAPE];
					printf("mainLoop(): Escape key press!\n");
					quitApplication = true;
					printf("mainLoop(): quitApplication = true!\n");
					break;

				default:
					this->currentScreenSurface = this->keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					printf("mainLoop(): Undefined key press!\n");
					break;
				}
			}
		}
		SDL_Rect strechRect;
		strechRect.x = 0;
		strechRect.y = 0;
		strechRect.w = this->SCREEN_WIDTH;
		strechRect.h = this->SCREEN_HEIGHT;

		SDL_BlitScaled(this->currentScreenSurface, NULL, this->screenSurface, &strechRect);
		SDL_UpdateWindowSurface(this->myAppWindow);
	}
}


void myApplication::close()
{
	SDL_FreeSurface(this->screenSurface);
	this->screenSurface = NULL;

	SDL_FreeSurface(this->currentScreenSurface);
	this->currentScreenSurface = NULL;
	
	SDL_DestroyWindow(this->myAppWindow);
	printf("close(): success!\n");
}