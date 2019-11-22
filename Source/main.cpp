#include "App.h"

using namespace Leadwerks;

int main(int argc, const char* argv[])
{
	App* app = new App;
	if (app->Start())
	{
		while (app->Loop()) {}

		delete app;

		return 0;
	}
	else
	{
		return 1;
	}
}