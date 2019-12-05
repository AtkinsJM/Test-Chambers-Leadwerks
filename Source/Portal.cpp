#include "Portal.h"
#include "PlayerController.h"
#include "SoundManager.h"
#include "GameManager.h"

Portal::Portal()
{
	bIsTeleporting = false;
	delay = 0.5f;
	destinationKey = 0;
	startTeleportTime = 0;
}

Portal::~Portal()
{
	Print("Portal destructor called");
}

void Portal::Attach()
{
	entity->SetCollisionType(Collision::Trigger);
	destinationKey = String::Int(entity->GetKeyValue("destinationKey"));
}

void Portal::UpdateWorld()
{	
	PickInfo pickInfo;
	//if (World::GetCurrent()->Pick(entity->GetPosition(true) - Vec3(0, 0.05f, 0), entity->GetPosition(true) + Vec3(0, 0.02f, 0), pickInfo, 0.0f, false, 11))
	if (World::GetCurrent()->Pick(Vec3(entity->GetPosition(true).x, -0.01f, entity->GetPosition(true).z), entity->GetPosition(true), pickInfo, 0.0f, false, 11))
	{
		if (std::find(currentCollisions.begin(), currentCollisions.end(), pickInfo.entity) == currentCollisions.end())
		{
			currentCollisions.push_back(pickInfo.entity);
		}
	}	

	if (bIsTeleporting)
	{
		float currentDelay = (Time::GetCurrent() - startTeleportTime) / 1000.0f;
		if (currentDelay >= delay)
		{
			bIsTeleporting = false;
			if (destinationKey == -1)
			{
				GameManager::QuitGame();
			}
			else
			{
				GameManager::StartLoadingLevel(destinationKey);
			}
		}
	}

	for (Entity* ent : currentCollisions)
	{
		if (std::find(collisionsLastFrame.begin(), collisionsLastFrame.end(), ent) == collisionsLastFrame.end())
		{
			OnBeginCollision(ent);
		}
	}

	for (Entity* ent : collisionsLastFrame)
	{
		if (std::find(currentCollisions.begin(), currentCollisions.end(), ent) == currentCollisions.end())
		{
			OnEndCollision(ent);
		}
	}
	collisionsLastFrame = currentCollisions;
	currentCollisions.clear();
}

void Portal::BeginTeleport()
{
	bIsTeleporting = true;
	startTeleportTime = Time::GetCurrent();

	SoundManager::Play("win");
	GameManager::StartUnloadingCurrentLevel();
}

void Portal::OnBeginCollision(Entity* otherEntity)
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

void Portal::OnEndCollision(Entity* otherEntity)
{

}
