#include "Teleport.h"
#include "PlayerController.h"
#include "SoundManager.h"

Teleport::Teleport()
{
	bIsTeleporting = false;
	target = nullptr;
	delay = 0.5f;
	startTeleportTime = 0;

	Collision::SetResponse(11, Collision::Character, Collision::Collide);
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
	if (!bIsTeleporting)
	{
		PickInfo pickInfo;
		if (World::GetCurrent()->Pick(entity->GetPosition(true) - Vec3(0, 0.05f, 0), entity->GetPosition(true) + Vec3(0, 0.05f, 0), pickInfo, 0.0f, false, 11))
		{
			if (std::find(currentCollisions.begin(), currentCollisions.end(), pickInfo.entity) == currentCollisions.end())
			{
				currentCollisions.push_back(pickInfo.entity);
			}
			
		}
	}
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

void Teleport::Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed)
{/*
	if (!bIsTeleporting)
	{
		PlayerController* player = static_cast<PlayerController*>(otherEntity->GetActor());
		if (player)
		{
			player->ToggleIsTeleporting();
			BeginTeleport(otherEntity);
		}
	}*/
}


void Teleport::BeginTeleport(Entity* otherEntity)
{
	bIsTeleporting = true;
	target = otherEntity;
	startTeleportTime = Time::GetCurrent();
}

void Teleport::OnBeginCollision(Entity* otherEntity)
{
	Print("Beginning collision with " + otherEntity->GetKeyValue("name", "Unknown"));
}

void Teleport::OnEndCollision(Entity* otherEntity)
{
	Print("Ending collision with " + otherEntity->GetKeyValue("name", "Unknown"));
}
