#include "Door.h"
#include "Constants.h"

Door::Door()
{
	requiredKeyType = DoorKeyType::BLUE_KEY;
}

Door::~Door()
{
}

void Door::Attach()
{
	requiredKeyType = static_cast<DoorKeyType>(String::Int(entity->GetKeyValue("requiredKeyType")));
	Print("Required key type:");
	Print(requiredKeyType);

	switch (requiredKeyType)
	{
	case DoorKeyType::RED_KEY:
		entity->SetColor(RED_COLOUR);
		break;
	case DoorKeyType::YELLOW_KEY:
		entity->SetColor(YELLOW_COLOUR);
		break;
	case DoorKeyType::GREEN_KEY:
		entity->SetColor(GREEN_COLOUR);
		break;
	case DoorKeyType::ORANGE_KEY:
		entity->SetColor(ORANGE_COLOUR);
		break;
	case DoorKeyType::PURPLE_KEY:
		entity->SetColor(PURPLE_COLOUR);
		break;
	case DoorKeyType::BLUE_KEY:
	default:
		entity->SetColor(BLUE_COLOUR);
		break;
	}
}

void Door::Unlock()
{
	entity->SetActor(nullptr);
	entity->Release();
}
