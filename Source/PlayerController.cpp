#include "PlayerController.h"

PlayerController::PlayerController()
{
	width = 1.0f;
	rotationSpeed = 30.0f;
	window = Window::GetCurrent();
	bIsRolling = false;
	rot = nullptr;
}

PlayerController::~PlayerController()
{
}

void PlayerController::Attach()
{
	Entity* playerStart = World::GetCurrent()->FindEntity("PlayerStart");

	Vec3 playerPos = playerStart ? playerStart->GetPosition() : Vec3(0, 2, 0);
	Vec3 playerRot = playerStart ? playerStart->GetRotation() : Vec3(0, 0, 0);

	//entity->SetPhysicsMode(Entity::CharacterPhysics);
	entity->SetGravityMode(false);
	entity->SetPosition(playerPos);
	entity->SetRotation(playerRot);
	entity->SetMass(1);
	Print("PlayerController attached to " + entity->GetClassNameA());

	Model* playerBox = Model::Box(width, entity);
	playerBox->SetPosition(0, (playerBox->GetScale().y) / 2, 0);
	playerBox->SetMass(1);
	playerBox->SetGravityMode(false);
	forwardRotationPoint = Vec3(0, 0, width/2);
	backRotationPoint = Vec3(0, 0, -width/2);
	leftRotationPoint = Vec3(-width/2, 0, 0);
	rightRotationPoint = Vec3(width/2, 0, 0);

	/*
	Print("Player start pos: ");
	Print(playerPos);
	Print("Forward rotation point: ");
	Print(forwardRotationPoint);
	Print("Left rotation point: ");
	Print(leftRotationPoint);
	*/
}

void PlayerController::UpdateWorld()
{	
	//entity->Move(1.0f * (Time::GetSpeed() / 30.0f), 0, 0);	// Time::GetSpeed() / 30.0f gives deltaTime
	if (bIsRolling && rot) 
	{ 
		return;
		if (angle < 95.0f)
		{
			float a = rotationSpeed * (Time::GetSpeed() / 30.0f);
			angle += a;
			rot->SetRotation(rot->GetRotation(true) + Vec3(0, 0, -a), true);
			entity->SetRotation(0, 0, 0);
			entity->SetPosition(0, relativePos.Length() * Math::Sin(-angle), relativePos.Length() * Math::Cos(-angle));
			Print("Rotation: ");
			Print(rot->GetRotation(true));
		}
		if (angle > 95.0f)
		{
			rot->SetRotation(rot->GetRotation(true) + Vec3(0, 0, 90.0f - angle), true);
			entity->SetParent(nullptr);
			rot->Release();
			bIsRolling = false;
		}
		return; 
	}
	if (window->KeyHit(Key::W) || window->KeyHit(Key::Up))
	{
		// TODO: raycast check to see if blocked

		Roll(forwardRotationPoint);
		/*rot = Model::Create();
		rot->SetMass(-1);
		rot->SetGravityMode(false);
		Vec3 playerP = entity->GetPosition(true);
		rot->SetPosition(Vec3(playerP.x, 0, playerP.z) + forwardRotationPoint);

		Print("Rot pos: ");
		Print(rot->GetPosition(true));
		entity->SetParent(rot);
		relativePos = -(rot->GetPosition(true));
		angle = 0.0f;
		point = entity->GetPosition(true) + forwardRotationPoint;
		bIsRolling = true;
		*/


	}
	else if (window->KeyDown(Key::S) || window->KeyDown(Key::Down))
	{
		// TODO: raycast check to see if blocked
		//Roll backward
	}
	else if (window->KeyDown(Key::A) || window->KeyDown(Key::Left))
	{
		// TODO: raycast check to see if blocked
		//Roll left
	}
	else if (window->KeyDown(Key::D) || window->KeyDown(Key::Right))
	{
		// TODO: raycast check to see if blocked
		//Roll right
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

int PlayerController::Roll(Vec3 rotationPoint)
{
	rot = Model::Create();
	rot->SetMass(-1);
	rot->SetGravityMode(false);
	Vec3 playerP = entity->GetPosition(true);
	rot->SetPosition(Vec3(playerP.x, 0, playerP.z) + forwardRotationPoint);

	Print("Rot pos: ");
	Print(rot->GetPosition(true));
	entity->SetParent(rot);
	relativePos = -(rot->GetPosition(true));
	bIsRolling = true;



	Print("Roll called");
	bIsRolling = true;
	//Print("Roll called");
	float angle = 0.0f;
	Vec3 point = entity->GetPosition(true) + rotationPoint;
	Vec3 up = Vec3(0, 1, 0);
	Vec3 axis = up.Cross(rotationPoint);
	
	while (angle < 90.0f)
	{
		Print("Rotating...");
		float a = rotationSpeed * (Time::GetSpeed() / 30.0f);
		angle += a;
		rot->SetRotation(rot->GetRotation(true) + Vec3(0, 0, -a), true);
		entity->SetRotation(0, 0, 0);
		entity->SetPosition(0, relativePos.Length() * Math::Sin(-angle), relativePos.Length() * Math::Cos(-angle));
		Print("Angle: " + String(angle));
		Print("Child rotation:");
		Print(entity->GetRotation(false));
	}
	rot->SetRotation(rot->GetRotation(true) + Vec3(0, 0, 90.0f - angle), true);
	entity->SetParent(nullptr);
	rot->Release();
	bIsRolling = false;
	return 0;
}
