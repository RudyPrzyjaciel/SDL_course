#pragma once
#include <SDL.h>
#include <string>
class myApplication
{
	bool loadMedia();
	SDL_Surface* loadSurface(std::string path);

	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_ESCAPE,
		KEY_PRESS_SURFACE_TOTAL,
	};

	SDL_Window* myAppWindow = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Surface* currentScreenSurface = NULL;
	SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
	SDL_Event event;
public:

	bool init();
	void mainLoop();
	void close();
};

