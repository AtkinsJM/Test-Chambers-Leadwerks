#include "Door.h"
#include "Constants.h"

Door::Door()
{
	requiredKeyType = DoorKeyType::BLUE_KEY;
}

Door::~Door()
{
	Print("Door destructor called");
}

void Door::Attach()
{
	requiredKeyType = static_cast<DoorKeyType>(String::Int(entity->GetKeyValue("requiredKeyType")));

	/*
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
	*/
}

void Door::Unlock()
{
	// TODO: find way of destroying actor, too (SetActor(nullptr)) - do via player?
	entity->Release();
}
