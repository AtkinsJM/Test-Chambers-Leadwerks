#include "Teleport.h"
#include "PlayerController.h"
#include "SoundManager.h"

Teleport::Teleport()
{
	bIsTeleporting = false;
	target = nullptr;
	delay = 1.0f;
}

Teleport::~Teleport()
{
}

void Teleport::Attach()
{
	entity->SetCollisionType(Collision::Trigger);

	Entity* waypoint = World::GetCurrent()->FindEntity(entity->GetKeyValue("destinationWaypoint"));
	if (waypoint)
	{
		destination = waypoint->GetPosition(true);
	}
	else
	{
		destination = entity->GetPosition(true);
	}
}

void Teleport::UpdateWorld()
{
	if (bIsTeleporting)
	{
		float currentDelay = (Time::GetCurrent() - startTeleportTime) / 1000.0f;
		if (currentDelay >= delay)
		{
			target->SetPosition(destination);
			// TODO: neaten this up (hold target as PlayerController instead of Entity(?)
			PlayerController* player = static_cast<PlayerController*>(target->GetActor());
			if (player)
			{
				player->ToggleIsTeleporting();
				SoundManager::Play("teleport");
			}
			target = nullptr;
			bIsTeleporting = false;
		}
	}
}

void Teleport::Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed)
{
	if (!bIsTeleporting)
	{
		PlayerController* player = static_cast<PlayerController*>(otherEntity->GetActor());
		if (player)
		{
			player->ToggleIsTeleporting();
			BeginTeleport(otherEntity);
		}
	}
}


void Teleport::BeginTeleport(Entity* otherEntity)
{
	bIsTeleporting = true;
	target = otherEntity;
	startTeleportTime = Time::GetCurrent();
}
