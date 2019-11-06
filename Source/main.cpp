#include "Leadwerks.h"
#include "PlayerController.h"

using namespace Leadwerks;

int main(int argc, const char* argv[])
{
	Window* gameWindow = Window::Create("My Game", 0, 0, 1024, 768);
	Context* context = Context::Create(gameWindow);
	World* world = World::Create();

	bool bUseVSync = false;

	Map::Load("Maps/game.map");
	
	Model* player = Model::Create();
	Actor* playerController = new PlayerController;
	player->SetActor(playerController);
	playerController->Release();
	   		
	while (true)
	{
		if (gameWindow->Closed() || gameWindow->KeyHit(Key::Escape)) { return false; }
		
		Time::Update();
		world->Update();
		world->Render();
		context->Sync(bUseVSync);
	}
	return 0;
}