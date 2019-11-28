#include "WinPortal.h"
#include "PlayerController.h"
#include "SoundManager.h"

WinPortal::WinPortal()
{
	bIsTeleporting = false;
	delay = 1.0f;
}

WinPortal::~WinPortal()
{
}

void WinPortal::Attach()
{
	entity->SetCollisionType(Collision::Trigger);
}

void WinPortal::UpdateWorld()
{
	if (bIsTeleporting)
	{
		float currentDelay = (Time::GetCurrent() - startTeleportTime) / 1000.0f;
		if (currentDelay >= delay)
		{
			SoundManager::Play("win");
			bIsTeleporting = false;
		}
	}
}

void WinPortal::Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed)
{
	if (!bIsTeleporting)
	{
		PlayerController* player = static_cast<PlayerController*>(otherEntity->GetActor());
		if (player)
		{
			player->ToggleIsTeleporting();
			BeginWin();
		}
	}
}

void WinPortal::BeginWin()
{
	bIsTeleporting = true;
	startTeleportTime = Time::GetCurrent();
}
