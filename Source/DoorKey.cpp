#include "DoorKey.h"

DoorKey::DoorKey()
{
	amplitude = 1.0f;
	frequency = 1.0f;
	rotationSpeed = 1.0f;

	bFloats = true;
	bRotates = true;
}

DoorKey::~DoorKey()
{
}

void DoorKey::Attach()
{
	startPosition = entity->GetPosition(true);

	amplitude = String::Float(entity->GetKeyValue("amplitude"));
	frequency = String::Float(entity->GetKeyValue("frequency"));
	rotationSpeed = String::Float(entity->GetKeyValue("rotationSpeed"));
	
	bFloats = entity->GetKeyValue("bFloats") == "true" ? true : false;
	bRotates = entity->GetKeyValue("bRotates") == "true" ? true : false;

	recordedTime = Time::GetCurrent();
}

void DoorKey::UpdateWorld()
{
	float deltaTime = (Time::GetCurrent() - recordedTime) / 1000.0f;
	recordedTime = Time::GetCurrent();
	if (bFloats)
	{
		entity->SetPosition(startPosition + Vec3(0, Math::Sin(360 * (Time::GetCurrent()/1000.0f) * frequency) * amplitude, 0), true);
	}
	if (bRotates)
	{
		entity->SetRotation(entity->GetRotation(true) + Vec3(0, rotationSpeed * deltaTime, 0), true);
	}
}
