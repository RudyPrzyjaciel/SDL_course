#include "myApplication.h"

int main(int argc, char* args[])
{
	myApplication myApp;

	myApp.init();
	myApp.mainLoop();
	myApp.close();

	return 0;
}
