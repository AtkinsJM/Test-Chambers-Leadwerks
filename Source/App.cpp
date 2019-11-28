#include "App.h"
#include "PlayerController.h"
#include "FollowCamera.h"
#include "Teleport.h"
#include "DoorKey.h"
#include "Door.h"
#include "SoundManager.h"
#include "WinPortal.h"

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

	SoundManager::LoadSounds();

	window->HideMouse();

	Model* player = Model::Box(1.28);
	Actor* playerController = new PlayerController;
	player->SetKeyValue("name", "Player");
	player->SetActor(playerController);
	//playerController->Release();

	Actor* followCamera = new FollowCamera(player);
	camera->SetActor(followCamera);
	
	Collision::SetResponse(Collision::Trigger, Collision::Prop, Collision::Trigger);

	for (int i = 0; i < world->CountEntities(); i++)
	{
		Entity* e = world->GetEntity(i);
		string tag = e->GetKeyValue("tag", "");
		if (tag == "Teleport")
		{
			Actor* teleport = new Teleport();
			e->SetActor(teleport);
		}
		else if (tag == "Key")
		{
			Actor* doorKey = new DoorKey();
			e->SetActor(doorKey);
		}
		else if (tag == "Door")
		{
			Actor* door = new Door();
			e->SetActor(door);
		}
		else if (tag == "WinPortal")
		{
			Actor* winPortal = new WinPortal();
			e->SetActor(winPortal);
		}
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