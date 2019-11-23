#include "PlayerController.h"

PlayerController::PlayerController()
{
	width = 1.0f;
	rotationSpeed = 45.0f;
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
	entity->SetPosition(Vec3(0, 1, 0));
	entity->SetRotation(playerRot);
	entity->SetMass(1);
	Print("PlayerController attached to " + entity->GetClassNameA());

	//Model* playerBox = Model::Box(width, entity);
	//playerBox->SetPosition(0, (playerBox->GetScale().y) / 2, 0);
	//playerBox->SetMass(1);
	//playerBox->SetGravityMode(false);
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
	/*
	if (Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.W))
	{
		if (!IsBlocked(Vector3.forward))
		{
			StartCoroutine(Roll(forwardRotationPoint));
		}

	}
	else if (Input.GetKey(KeyCode.DownArrow) || Input.GetKey(KeyCode.S))
	{
		if (!IsBlocked(Vector3.back))
		{
			StartCoroutine(Roll(backRotationPoint));
		}
	}
	else if (Input.GetKey(KeyCode.LeftArrow) || Input.GetKey(KeyCode.A))
	{
		if (!IsBlocked(Vector3.left))
		{
			StartCoroutine(Roll(leftRotationPoint));
		}
	}
	else if (Input.GetKey(KeyCode.RightArrow) || Input.GetKey(KeyCode.D))
	{
		if (!IsBlocked(Vector3.right))
		{
			StartCoroutine(Roll(rightRotationPoint));
		}
	}
	*/
}

void PlayerController::UpdatePhysics()
{
}

void PlayerController::StartRolling(Vec3 rotationPoint)
{
	bIsRolling = true;
	rotationAngle = 0.0f;
	rotationOrigin = entity->GetPosition(true) + rotationPoint;
	Print(rotationOrigin);
	rollingDirection = Vec3(rotationPoint.x != 0 ? Math::Abs(rotationPoint.x) / rotationPoint.x : 0, rotationPoint.y != 0 ? Math::Abs(rotationPoint.y) / rotationPoint.y : 0, rotationPoint.z != 0 ? Math::Abs(rotationPoint.z) / rotationPoint.z : 0);
}

void PlayerController::Roll()
{
	float a = rotationSpeed * (Time::GetSpeed() / 30.0f);
	rotationAngle += a;
	float offsetAngle = 45.0f + rotationAngle;
	Vec3 offset = Vec3(distanceFromOrigin * Math::Cos(offsetAngle) * -rollingDirection.x, distanceFromOrigin * Math::Sin(offsetAngle), distanceFromOrigin * Math::Cos(offsetAngle) * -rollingDirection.z);
	entity->SetPosition(rotationOrigin + offset, true);
	Vec3 rotationToApply = Vec3(rollingDirection.z * a, 0, rollingDirection.x * -a);
	entity->SetRotation(entity->GetRotation(true) + rotationToApply, true);
	
	if (rotationAngle > 90.0f)
	{
		// TODO refactor to avoid repetition of code (use ternary operator above?)
		offsetAngle = 45.0f + 90.0f;
		offset = Vec3(distanceFromOrigin * Math::Cos(offsetAngle) * -rollingDirection.x, distanceFromOrigin * Math::Sin(offsetAngle), distanceFromOrigin * Math::Cos(offsetAngle) * -rollingDirection.z);
		entity->SetPosition(rotationOrigin + offset, true);
		entity->SetRotation(Vec3(0,0,0), true);
		bIsRolling = false;
	}
}
