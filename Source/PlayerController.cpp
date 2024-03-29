#include "PlayerController.h"
#include "Teleport.h"
#include "DoorKey.h"
#include "Door.h"
#include "SoundManager.h"
#include "UserInterface.h"
#include "KeyManager.h"
#include "GameManager.h"
#include "Lever.h"

PlayerController::PlayerController()
{
	width = 1.28f;
	rotationSpeed = 180.0f;
	rotationAngle = 0;
	window = Window::GetCurrent();
	bIsRolling = false;
	distanceFromOrigin = sqrt((width / 2) * (width / 2) * 2);

	bIsTeleporting = false;
	bIsBeingTransported = false;
	
	keyManager = new KeyManager();

	// Set up custom collision type for pick
	Collision::SetResponse(10, Collision::Scene, Collision::Collide);
	Collision::SetResponse(10, Collision::Prop, Collision::Collide);
}

PlayerController::~PlayerController()
{
	delete keyManager;
}

void PlayerController::Attach()
{
	Entity* playerStart = World::GetCurrent()->FindEntity("PlayerStart");

	Vec3 playerPos = playerStart ? playerStart->GetPosition() : Vec3(0, 2, 0);
	Vec3 playerRot = playerStart ? playerStart->GetRotation() : Vec3(0, 0, 0);

	// Set up physics on player
	entity->SetPhysicsMode(Entity::RigidBodyPhysics);
	entity->SetCollisionType(Collision::Character);
	entity->SetShape(Shape::Box(0, 0, 0, 0, 0, 0, width, width, width));
	entity->SetGravityMode(false);
	entity->SetMass(1);
	entity->SetShadowMode(Light::Dynamic);

	// TODO: make a variable
	entity->SetColor(0.40f, 0.40f, 0.40f);

	entity->SetPosition(playerPos);
	entity->SetRotation(playerRot);


	backRotationPoint = Vec3(0, -width / 2, -width/2);
	forwardRotationPoint = Vec3(0, -width / 2, width/2);
	leftRotationPoint = Vec3(-width/2, -width / 2, 0);
	rightRotationPoint = Vec3(width/2, -width / 2, 0);
}

void PlayerController::UpdateWorld()
{	
	if (bIsRolling) 
	{ 
		if (rotationAngle < 90.0f)
		{
			Roll();
		}
		return;
	}

	GameManager::SetCurrentGroundHeight(entity->GetPosition(true).y - width / 2.0f);

	if (bIsTeleporting || bIsBeingTransported) { return; }

	if (window->KeyDown(Key::W) || window->KeyDown(Key::Up))
	{
		if (!IsBlocked(Vec3(0, 0, width)))
		{
			StartRolling(forwardRotationPoint);
		}	
	}
	else if (window->KeyDown(Key::S) || window->KeyDown(Key::Down))
	{
		if (!IsBlocked(Vec3(0, 0, -width)))
		{
			StartRolling(backRotationPoint);
		}
	}
	else if (window->KeyDown(Key::A) || window->KeyDown(Key::Left))
	{
		if (!IsBlocked(Vec3(-width, 0, 0)))
		{
			StartRolling(leftRotationPoint);
		}
	}
	else if (window->KeyDown(Key::D) || window->KeyDown(Key::Right))
	{
		if (!IsBlocked(Vec3(width, 0, 0)))
		{
			StartRolling(rightRotationPoint);
		}
	}

	if (window->KeyHit(Key::E))
	{
		Door* door = IsDoorPresent();
		if (door)
		{
			if (keyManager->HasDoorKey(door->GetRequiredKeyType()))
			{
				door->Unlock();
				SoundManager::Play("doorUnlocked");
			}
			else
			{
				SoundManager::Play("doorLocked");
			}
		}

		Lever* lever = IsLeverPresent();
		if (lever)
		{
			lever->PullLever();
		}
	}
}

void PlayerController::StartRolling(Vec3 rotationPoint)
{
	bIsRolling = true;
	rotationAngle = 0.0f;
	rotationOrigin = entity->GetPosition(true) + rotationPoint;
	rollingDirection = Vec3(rotationPoint.x != 0 ? Math::Abs(rotationPoint.x) / rotationPoint.x : 0, 0, rotationPoint.z != 0 ? Math::Abs(rotationPoint.z) / rotationPoint.z : 0);
}

void PlayerController::Roll()
{
	// Get change in angle
	float a = rotationSpeed * (Time::GetSpeed() / 30.0f);
	rotationAngle += a;
	rotationAngle = rotationAngle > 90.0f ? 90.0f : rotationAngle;
	// Calculate angle between centre of entity and rotationOrigin
	float offsetAngle = 45.0f + rotationAngle;
	// Calculate spacial offset between centre of entity and rotationOrigin
	Vec3 offset = Vec3(distanceFromOrigin * Math::Cos(offsetAngle) * -rollingDirection.x, distanceFromOrigin * Math::Sin(offsetAngle), distanceFromOrigin * Math::Cos(offsetAngle) * -rollingDirection.z);
	entity->SetPosition(rotationOrigin + offset, true);
	Vec3 rotationToApply = Vec3(rollingDirection.z * a, 0, rollingDirection.x * -a);
	entity->SetRotation(entity->GetRotation(true) + rotationToApply, true);
	
	if (rotationAngle >= 90.0f)
	{
		// Finish rolling by zeroing out rotation
		entity->SetRotation(Vec3(0,0,0), true);
		SoundManager::Play("roll");
		bIsRolling = false;
	}
}

bool PlayerController::IsBlocked(Vec3 direction)
{
	PickInfo pickInfo;
	targetPosition = entity->GetPosition(true) + direction;
	// Returns true if there is an obstacle in - or no ground below - the player's target position
	if (World::GetCurrent()->Pick(entity->GetPosition(true), targetPosition, pickInfo, 0.0f, false, 10) ||
		!World::GetCurrent()->Pick(targetPosition, targetPosition + Vec3(0, -width, 0), pickInfo, 0.0f, false, 10))
	{
		return true;
	}
	return false;
}

Door* PlayerController::IsDoorPresent()
{
	// Raycast in all four direction to see if player is adjacent to a door. If there is a door, return it
	PickInfo pickInfo;
	if ((World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(0, 0, width), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Door") ||
		(World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(0, 0, -width), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Door") ||
		(World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(width, 0, 0), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Door") ||
		(World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(-width, 0, 0), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Door"))
	{
		Door* door = static_cast<Door*>(pickInfo.entity->GetActor());
		if (door)
		{
			return door;
		}
	}
	return nullptr;
}

Lever* PlayerController::IsLeverPresent()
{
	// Raycast in all four direction to see if player is adjacent to a lever. If there is a lever, return it
	PickInfo pickInfo;
	if ((World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(0, 0, width), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Lever") ||
		(World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(0, 0, -width), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Lever") ||
		(World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(width, 0, 0), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Lever") ||
		(World::GetCurrent()->Pick(entity->GetPosition(true), entity->GetPosition(true) + Vec3(-width, 0, 0), pickInfo)) && (pickInfo.entity->GetKeyValue("tag") == "Lever"))
	{
		Lever* lever = static_cast<Lever*>(pickInfo.entity->GetActor());
		if (lever)
		{
			return lever;
		}
	}
	return nullptr;
}
