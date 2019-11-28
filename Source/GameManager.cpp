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
	// TODO: find some way to clear the world that doesn't cause game to crash!
	Map::Load(levelMap[levelKey]);
	if (app)
	{
		app->SetupWorld();
	}
}

void GameManager::QuitGame()
{
	bIsGameActive = false;
}
