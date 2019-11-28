#include "MenuPortal.h"
#include "GameManager.h"

MenuPortal::MenuPortal()
{
}

MenuPortal::~MenuPortal()
{
}

void MenuPortal::Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed)
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
