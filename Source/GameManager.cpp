#include "GameManager.h"
#include "App.h"

std::map<int, string> GameManager::levelMap;
bool GameManager::bIsGameActive;

App* GameManager::app;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::LoadMaps()
{
	levelMap[0] = "Maps/menu.map";
	levelMap[1] = "Maps/level1.map";
	levelMap[2] = "Maps/level2.map";
	levelMap[3] = "Maps/level3.map";
}

void GameManager::LoadLevel(int levelKey)
{
	if (!app) { return; }
	
	Print("Entity count 1:");
	Print(app->world->CountEntities());
	app->world->Clear(true);
	Print("Entity count 2:");
	Print(app->world->CountEntities());
	for (int i = 0; i < app->world->CountEntities(); i++)
	{
		Entity* e = app->world->GetEntity(i); 
		Print(e->GetKeyValue("name", "Unknown"));
	}
	if (app->camera)
	{
		app->camera->Release();
		app->camera = nullptr;
	}
		
	app->camera = Camera::Create();
	
	Map::Load(levelMap[levelKey]);

	app->SetupMap();
	Print("Entity count 3:");
	Print(app->world->CountEntities());
	for (int i = 0; i < app->world->CountEntities(); i++)
	{
		Entity* e = app->world->GetEntity(i);
		Print(e->GetKeyValue("name", "Unknown"));
	}
}

void GameManager::QuitGame()
{
	bIsGameActive = false;
}
