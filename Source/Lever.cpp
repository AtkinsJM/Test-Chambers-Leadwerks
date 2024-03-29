#include "Lever.h"
#include "SoundManager.h"
#include "LaserGate.h"

Lever::Lever()
{
	leverArm = nullptr;
	armAngle = 25.0f;
}

Lever::~Lever()
{
}

void Lever::Attach()
{
	leverArm = entity->FindChild("ArmPivot");
	if (leverArm)
	{
		leverArm->SetRotation(0, 0, armAngle, true);
	}

	int numTargets = String::Int(entity->GetKeyValue("numTargets"));

	if (numTargets > 0)
	{
		for (int i = 1; i <= numTargets; i++)
		{
			string keyName = "target" + String(i);
			if (entity->GetKeyValue(keyName) != "")
			{
				Entity* targetEnt = World::GetCurrent()->FindEntity(entity->GetKeyValue(keyName));
				if (targetEnt)
				{
					LaserGate* target = static_cast<LaserGate*>(targetEnt->GetActor());
					if (target)
					{
						targets.push_back(target);
					}
				}
			}
		}
	}
}

void Lever::UpdateWorld()
{
}

void Lever::PullLever()
{
	for (LaserGate* laserGate : targets)
	{
		laserGate->ToggleGate();
	}
	if (leverArm)
	{
		armAngle = -armAngle;
		leverArm->SetRotation(0, 0, armAngle, true);
		if (armAngle > 0)
		{
			SoundManager::Play("lever1");
		}
		else
		{
			SoundManager::Play("lever2");
		}
	}
}
