#include "DoorKey.h"
#include "Constants.h"

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

	Print("Key destructor called");
}

void DoorKey::Attach()
{
	entity->SetCollisionType(Collision::Trigger);
	entity->SetSweptCollisionMode(true);
	
	parent = entity->GetParent();
	if (parent)
	{
		startPosition = parent->GetPosition(true);
	}
	model = entity->GetChild(0);
	if (model)
	{
		model->SetCollisionType(Collision::None);
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
			model->SetColor(RED_COLOUR);
			break;
		case DoorKeyType::YELLOW_KEY:
			model->SetColor(YELLOW_COLOUR);
			break;
		case DoorKeyType::GREEN_KEY:
			model->SetColor(GREEN_COLOUR);
			break;
		case DoorKeyType::ORANGE_KEY:
			model->SetColor(ORANGE_COLOUR);
			break;
		case DoorKeyType::PURPLE_KEY:
			model->SetColor(PURPLE_COLOUR);
			break;
		case DoorKeyType::BLUE_KEY:
		default:
			model->SetColor(BLUE_COLOUR);
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

void DoorKey::Destroy()
{
	entity->SetActor(nullptr);
	parent->Release();
}
