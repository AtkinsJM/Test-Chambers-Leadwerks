#include "App.h"
#include "PlayerController.h"
#include "FollowCamera.h"
#include "Teleport.h"
#include "DoorKey.h"
#include "Door.h"
#include "SoundManager.h"
#include "Portal.h"
#include "GameManager.h"
#include "FadeScreen.h"

using namespace Leadwerks;

App::App() : window(NULL), context(NULL), world(NULL), fadeScreen(NULL)
{
	bUseVSync = false;
}

App::~App()
{
	delete fadeScreen;
	delete world;
	delete window;
}

bool App::Start()
{
	window = Window::Create("Test Chambers", 0, 0, 1280, 720);
	context = Context::Create(window);
	world = World::Create();
	
	GameManager::SetIsGameActive(true);
	GameManager::LoadMaps();
	SoundManager::LoadSounds();

	fadeScreen = new FadeScreen();
	GameManager::SetFadeScreen(fadeScreen);

	window->HideMouse();

	Collision::SetResponse(Collision::Trigger, Collision::Prop, Collision::Trigger);
	
	GameManager::StartLoadingLevel(0);
	return true;
}

bool App::Loop()
{
	if (window->Closed() || window->KeyHit(Key::Escape) || GameManager::IsGameActive() == false) { return false; }

	if (GameManager::IsLoadingLevel())
	{
		world->Clear();
		GameManager::LoadLevel();
		PopulateActors();
	}
	
	Time::Update();
	world->Update();
	world->Render();
	context->Sync(bUseVSync);
	fadeScreen->Process();
	return true;
}

void App::PopulateActors()
{
	Model* player = Model::Box(1.28);	
	player->SetKeyValue("name", "Player");
	Actor* playerController = new PlayerController;
	player->SetActor(playerController);

	Camera* camera = Camera::Create();
	camera->SetKeyValue("name", "Camera");
	Actor* followCamera = new FollowCamera(player);
	camera->SetActor(followCamera);

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
}
