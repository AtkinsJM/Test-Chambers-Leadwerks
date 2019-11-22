#include "App.h"
#include "PlayerController.h"
#include "FollowCamera.h"

using namespace Leadwerks;

App::App() : window(NULL), context(NULL), world(NULL), camera(NULL)
{

	bUseVSync = false;
}

App::~App()
{
	delete world;
	delete window;
}

bool App::Start()
{
	window = Window::Create("Test Chambers", 0, 0, 1280, 720);
	context = Context::Create(window);
	world = World::Create();
	camera = Camera::Create();

	Map::Load("Maps/game.map");

	window->HideMouse();

	Model* player = Model::Create();
	Actor* playerController = new PlayerController;
	player->SetKeyValue("name", "Player");
	player->SetActor(playerController);
	//playerController->Release();

	Actor* followCamera = new FollowCamera(player);
	camera->SetActor(followCamera);

	while (true)
	{
		if (window->Closed() || window->KeyHit(Key::Escape)) { return false; }

		Time::Update();
		world->Update();
		world->Render();
		context->Sync(bUseVSync);
	}

	return true;
}

bool App::Loop()
{
	if (window->Closed() || window->KeyHit(Key::Escape)) { return false; }

	Time::Update();
	world->Update();
	world->Render();
	context->Sync(bUseVSync);
	return true;
}