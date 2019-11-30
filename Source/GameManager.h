#pragma once
#include "Leadwerks.h"
#include <map>

using namespace Leadwerks;

class App;
class FadeScreen;

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
	
	FORCEINLINE static void SetIsGameActive(bool val) { bIsGameActive = val; }
	FORCEINLINE static bool IsGameActive() { return bIsGameActive; }

	FORCEINLINE static bool IsLoadingLevel() { return bIsLoadingLevel; }

	FORCEINLINE static void SetFadeScreen(FadeScreen* fs) { fadeScreen = fs; }

private:
	static std::map<int, string> levelMap;

	static bool bIsGameActive;
	
	static bool bIsLoadingLevel;

	static int levelToLoad;

	static FadeScreen* fadeScreen;
};