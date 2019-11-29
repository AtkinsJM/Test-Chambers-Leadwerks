#include "App.h"
#include "PlayerController.h"
#include "FollowCamera.h"
#include "Teleport.h"
#include "DoorKey.h"
#include "Door.h"
#include "SoundManager.h"
#include "Portal.h"
#include "GameManager.h"

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
	

	GameManager::SetApp(this);
	GameManager::SetIsGameActive(true);
	GameManager::LoadMaps();
	SoundManager::LoadSounds();

	window->HideMouse();

	Collision::SetResponse(Collision::Trigger, Collision::Prop, Collision::Trigger);

	GameManager::LoadLevel(0);

	for (int i = 0; i < world->CountEntities(); i++)
	{
		Entity* e = world->GetEntity(i);
		string tag = e->GetKeyValue("tag", "");
		if (tag == "Key")
		{
			Actor* doorKey = new DoorKey();
			e->SetActor(doorKey);
			doorKey = nullptr;
		}
		else if (tag == "Door")
		{
			Actor* door = new Door();
			e->SetActor(door);
			door = nullptr;
		}
		else if (tag == "Portal")
		{
			Actor* portal = new Portal();
			e->SetActor(portal);
			portal = nullptr;
		}
	}


	return true;
}

bool App::Loop()
{
	if (!world) { return true; }
	if (window->Closed() || window->KeyHit(Key::Escape) || GameManager::GetIsGameActive() == false) { return false; }

	Time::Update();
	world->Update();
	world->Render();
	context->Sync(bUseVSync);
	return true;
}

void App::SetupMap()
{
	//camera = Camera::Create();
	Model* player = Model::Box(1.28);
	Actor* playerController = new PlayerController;
	player->SetKeyValue("name", "Player");
	player->SetActor(playerController);

	Actor* followCamera = new FollowCamera(player);
	if (camera)
	{
		camera->SetActor(followCamera);
	}
	for (int i = 0; i < world->CountEntities(); i++)
	{
		Entity* e = world->GetEntity(i);
		string tag = e->GetKeyValue("tag", "");
		if (tag == "Teleport")
		{
			Actor* teleport = new Teleport();
			e->SetActor(teleport);
			teleport = nullptr;
		}
	}
	// TODO: work out why following actor assignments cause crash
	/*
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
		else if (tag == "Portal")
		{
			Actor* portal = new Portal();
			e->SetActor(portal);
		}
	}
	*/
}
