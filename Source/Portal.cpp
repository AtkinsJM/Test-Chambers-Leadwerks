#include "Portal.h"
#include "PlayerController.h"
#include "SoundManager.h"
#include "GameManager.h"

Portal::Portal()
{
	bIsTeleporting = false;
	delay = 1.0f;
	destinationKey = 0;
}

Portal::~Portal()
{
}

void Portal::Attach()
{
	entity->SetCollisionType(Collision::Trigger);
	destinationKey = String::Int(entity->GetKeyValue("destinationKey"));
}

void Portal::UpdateWorld()
{
	if (bIsTeleporting)
	{
		float currentDelay = (Time::GetCurrent() - startTeleportTime) / 1000.0f;
		if (currentDelay >= delay)
		{
			SoundManager::Play("win");
			bIsTeleporting = false;
			if (destinationKey == -1)
			{
				Print("Quitting...");
				GameManager::QuitGame();
			}
			else
			{
				Print("Loading level...");
				GameManager::LoadLevel(destinationKey);
			}
			
		}
	}
}

void Portal::Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed)
{
	if (!bIsTeleporting)
	{
		PlayerController* player = static_cast<PlayerController*>(otherEntity->GetActor());
		if (player)
		{
			player->ToggleIsTeleporting();
			BeginTeleport();
		}
	}
}

void Portal::BeginTeleport()
{
	bIsTeleporting = true;
	startTeleportTime = Time::GetCurrent();
}
