#include "PlayerController.h"

PlayerController::PlayerController()
{
	width = 1.28f;
	rotationSpeed = 90.0f;
	window = Window::GetCurrent();
	bIsRolling = false;
	distanceFromOrigin = sqrt((width / 2) * (width / 2) * 2);
}

PlayerController::~PlayerController()
{
}

void PlayerController::Attach()
{
	Entity* playerStart = World::GetCurrent()->FindEntity("PlayerStart");

	Vec3 playerPos = playerStart ? playerStart->GetPosition() : Vec3(0, 2, 0);
	Vec3 playerRot = playerStart ? playerStart->GetRotation() : Vec3(0, 0, 0);

	entity->SetPhysicsMode(Entity::RigidBodyPhysics);
	entity->SetGravityMode(false);
	entity->SetPosition(playerPos);
	entity->SetRotation(playerRot);
	entity->SetMass(1);

	rightRotationPoint = Vec3(0, -width / 2, -width/2);
	leftRotationPoint = Vec3(0, -width / 2, width/2);
	backRotationPoint = Vec3(-width/2, -width / 2, 0);
	forwardRotationPoint = Vec3(width/2, -width / 2, 0);
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
	if (window->KeyDown(Key::W) || window->KeyDown(Key::Up))
	{
		// TODO: raycast check to see if blocked
		StartRolling(forwardRotationPoint);

	}
	else if (window->KeyDown(Key::S) || window->KeyDown(Key::Down))
	{
		// TODO: raycast check to see if blocked
		StartRolling(backRotationPoint);
	}
	else if (window->KeyDown(Key::A) || window->KeyDown(Key::Left))
	{
		// TODO: raycast check to see if blocked
		StartRolling(leftRotationPoint);
	}
	else if (window->KeyDown(Key::D) || window->KeyDown(Key::Right))
	{
		// TODO: raycast check to see if blocked
		StartRolling(rightRotationPoint);
	}
}

void PlayerController::UpdatePhysics()
{
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
		bIsRolling = false;
	}
}
