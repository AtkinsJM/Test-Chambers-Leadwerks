#pragma once
#include "Leadwerks.h"
#include <map>

using namespace Leadwerks;

class App;

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
	
	FORCEINLINE static void SetApp(App* a) { app = a; }

	FORCEINLINE static void SetIsGameActive(bool val) { bIsGameActive = val; }
	FORCEINLINE static bool GetIsGameActive() { return bIsGameActive; }

	FORCEINLINE static bool IsLoadingLevel() { return bIsLoadingLevel; }

private:
	static std::map<int, string> levelMap;

	static bool bIsGameActive;

	static App* app;

	static bool bIsLoadingLevel;

	static int levelToLoad;
};