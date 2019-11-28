#include "GameManager.h"

std::map<int, string> GameManager::levelMap;

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
	Map::Load(levelMap[levelKey]);
}
