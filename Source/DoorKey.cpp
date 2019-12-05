#include "DoorKey.h"
#include "Constants.h"
#include "PlayerController.h"
#include "KeyManager.h"

DoorKey::DoorKey()
{
	amplitude = 0.2f;
	frequency = 0.5f;
	rotationSpeed = 90.0f;
	recordedTime = 0;

	bFloats = true;
	bRotates = true;
	doorKeyType = DoorKeyType::BLUE_KEY;

	model = nullptr;
}

DoorKey::~DoorKey()
{

}

void DoorKey::Attach()
{
	entity->SetCollisionType(Collision::Trigger);
	entity->SetSweptCollisionMode(true);
	model = entity->GetChild(0);
	if (model)
	{
		startPosition = model->GetPosition(true);
		model->SetCollisionType(Collision::None, true);
		model->SetShadowMode(2, true);
	}

	amplitude = String::Float(entity->GetKeyValue("amplitude"));
	frequency = String::Float(entity->GetKeyValue("frequency"));
	rotationSpeed = String::Float(entity->GetKeyValue("rotationSpeed"));
	
	bFloats = entity->GetKeyValue("bFloats") == "true" ? true : false;
	bRotates = entity->GetKeyValue("bRotates") == "true" ? true : false;

	doorKeyType = static_cast<DoorKeyType>(String::Int(entity->GetKeyValue("doorKeyType")));

	switch (doorKeyType)
	{
		case DoorKeyType::RED_KEY:
			model->SetColor(RED_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::YELLOW_KEY:
			model->SetColor(YELLOW_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::GREEN_KEY:
			model->SetColor(GREEN_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::ORANGE_KEY:
			model->SetColor(ORANGE_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::PURPLE_KEY:
			model->SetColor(PURPLE_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::BLUE_KEY:
		default:
			model->SetColor(BLUE_COLOUR, COLOR_DIFFUSE, true);
			break;
	}

	recordedTime = Time::GetCurrent();
}

void DoorKey::UpdateWorld()
{
	if (!model) { return; }
	float deltaTime = (Time::GetCurrent() - recordedTime) / 1000.0f;
	recordedTime = Time::GetCurrent();

	if (bFloats)
	{
		model->SetPosition(startPosition + Vec3(0, Math::Sin(360 * (Time::GetCurrent()/1000.0f) * frequency) * amplitude, 0), true);
	}

	if (bRotates)
	{
		model->SetRotation(model->GetRotation(true) + Vec3(0, rotationSpeed * deltaTime, 0), true);
	}

	PickInfo pickInfo;

	if (World::GetCurrent()->Pick(Vec3(entity->GetPosition(true).x, -0.01f, entity->GetPosition(true).z), model->GetPosition(true), pickInfo, 0.0f, false, 11))
	{
		if (std::find(currentCollisions.begin(), currentCollisions.end(), pickInfo.entity) == currentCollisions.end())
		{
			currentCollisions.push_back(pickInfo.entity);
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

void DoorKey::Destroy()
{
	entity->Release();
}

void DoorKey::OnBeginCollision(Entity* otherEntity)
{
	PlayerController* player = static_cast<PlayerController*>(otherEntity->GetActor());
	if (player)
	{
		player->GetKeyManager()->PickUpDoorKey(this);
	}		
}

void DoorKey::OnEndCollision(Entity* otherEntity)
{
}
