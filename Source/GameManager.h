#pragma once
#include "Leadwerks.h"
#include <map>

using namespace Leadwerks;

class UserInterface;

class GameManager : public Actor
{
public:
	GameManager();
	~GameManager();
	//virtual void Attach();
	//virtual void Detach();
	//virtual void UpdateWorld();
	//virtual void UpdateMatrix();
	//virtual void UpdatePhysics();
	//virtual void Wake();
	//virtual void Sleep();
	//virtual void Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed);
	//virtual void PostRender();
	//virtual void Draw();
	//virtual void DrawEach(Camera* camera);
	//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);

	static void LoadMaps();

	static void LoadLevel();

	static void QuitGame();

	static void StartLoadingLevel(int levelKey);

	static void StartUnloadingCurrentLevel();

	static void CreateImage(string imageKey, int x, int y, int width, int height);
	
	FORCEINLINE static void SetIsGameActive(bool val) { bIsGameActive = val; }
	FORCEINLINE static bool IsGameActive() { return bIsGameActive; }

	FORCEINLINE static bool IsLoadingLevel() { return bIsLoadingLevel; }

	FORCEINLINE static void SetUserInterface(UserInterface* ui) { userInterface = ui; }

	FORCEINLINE static void SetCurrentGroundHeight(float val) { currentGroundHeight = val; }
	FORCEINLINE static float CurrentGroundHeight() { return currentGroundHeight; }

private:
	static std::map<int, string> levelMap;

	static bool bIsGameActive;
	
	static bool bIsLoadingLevel;

	static int levelToLoad;

	static UserInterface* userInterface;

	static float currentGroundHeight;
};