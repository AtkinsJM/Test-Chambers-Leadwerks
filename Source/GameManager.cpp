#include "GameManager.h"
#include "App.h"
#include "PlayerController.h"
#include "FollowCamera.h"
#include "Teleport.h"
#include "DoorKey.h"
#include "Door.h"
#include "SoundManager.h"
#include "Portal.h"
#include "UserInterface.h"

std::map<int, string> GameManager::levelMap;
bool GameManager::bIsGameActive;
bool GameManager::bIsLoadingLevel;
int GameManager::levelToLoad;
UserInterface* GameManager::userInterface;
float GameManager::currentGroundHeight;


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

void GameManager::StartLoadingLevel(int levelKey)
{
	levelToLoad = levelKey;
	bIsLoadingLevel = true;
}

void GameManager::StartUnloadingCurrentLevel()
{
	userInterface->FadeOut(0.5f);
}

void GameManager::CreateImage(string imageKey, int x, int y, int width, int height)
{
	userInterface->CreateImage(imageKey, x, y, width, height);
}

void GameManager::LoadLevel()
{	
	Map::Load(levelMap[levelToLoad]);
	bIsLoadingLevel = false;
}

void GameManager::QuitGame()
{
	bIsGameActive = false;
}
