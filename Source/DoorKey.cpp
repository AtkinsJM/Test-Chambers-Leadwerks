#include "DoorKey.h"

DoorKey::DoorKey()
{
	amplitude = 0.2f;
	frequency = 0.5f;
	rotationSpeed = 90.0f;

	bFloats = true;
	bRotates = true;
	doorKeyType = DoorKeyType::BLUE_KEY;

	parent = nullptr;
}

DoorKey::~DoorKey()
{
}

void DoorKey::Attach()
{
	entity->SetCollisionType(Collision::Trigger);
	
	parent = entity->GetParent();
	if (parent)
	{
		startPosition = parent->GetPosition(true);
	}

	amplitude = String::Float(entity->GetKeyValue("amplitude"));
	frequency = String::Float(entity->GetKeyValue("frequency"));
	rotationSpeed = String::Float(entity->GetKeyValue("rotationSpeed"));
	
	bFloats = entity->GetKeyValue("bFloats") == "true" ? true : false;
	bRotates = entity->GetKeyValue("bRotates") == "true" ? true : false;

	doorKeyType = static_cast<DoorKeyType>(String::Int(entity->GetKeyValue("doorKeyType")));

	Print(doorKeyType);

	switch (doorKeyType)
	{
		case DoorKeyType::RED_KEY:
			entity->SetColor(RED_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::YELLOW_KEY:
			entity->SetColor(YELLOW_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::GREEN_KEY:
			entity->SetColor(GREEN_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::ORANGE_KEY:
			entity->SetColor(ORANGE_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::PURPLE_KEY:
			entity->SetColor(PURPLE_COLOUR, COLOR_DIFFUSE, true);
			break;
		case DoorKeyType::BLUE_KEY:
		default:
			entity->SetColor(BLUE_COLOUR, COLOR_DIFFUSE, true);
			break;
	}

	recordedTime = Time::GetCurrent();
}

void DoorKey::UpdateWorld()
{
	if (!parent) { return; }

	float deltaTime = (Time::GetCurrent() - recordedTime) / 1000.0f;
	recordedTime = Time::GetCurrent();

	if (bFloats)
	{
		parent->SetPosition(startPosition + Vec3(0, Math::Sin(360 * (Time::GetCurrent()/1000.0f) * frequency) * amplitude, 0), true);
	}

	if (bRotates)
	{
		parent->SetRotation(parent->GetRotation(true) + Vec3(0, rotationSpeed * deltaTime, 0), true);
	}
}
