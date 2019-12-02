#include "KeyManager.h"
#include "DoorKey.h"
#include "SoundManager.h"
#include "GameManager.h"

KeyManager::KeyManager()
{
	keysPickedUp = 0;
}

KeyManager::~KeyManager()
{
}

void KeyManager::PickUpDoorKey(DoorKey* doorKey)
{
	doorKeySequence |= static_cast<int>(doorKey->GetDoorKeyType());
	doorKey->Destroy();
	SoundManager::Play("pickup");

	string imageKey = "";
	switch (doorKey->GetDoorKeyType())
	{
	case DoorKeyType::BLUE_KEY:
		imageKey = "blueKeySprite";
		break;
	case DoorKeyType::RED_KEY:
		imageKey = "redKeySprite";
		break;
	case DoorKeyType::YELLOW_KEY:
		imageKey = "yellowKeySprite";
		break;
	case DoorKeyType::GREEN_KEY:
		imageKey = "greenKeySprite";
		break;
	case DoorKeyType::ORANGE_KEY:
		imageKey = "orangeKeySprite";
		break;
	case DoorKeyType::PURPLE_KEY:
		imageKey = "purpleKeySprite";
		break;
	default:
		break;
	}
	int x = 12 + (keysPickedUp * 36);
	int y = Window::GetCurrent()->GetClientHeight() - 72;

	GameManager::CreateImage(imageKey, x, y, 24, 60);

	keysPickedUp++;
}

bool KeyManager::HasDoorKey(DoorKeyType doorKeyType)
{
	return (doorKeySequence & static_cast<int>(doorKeyType)) == static_cast<int>(doorKeyType);
}