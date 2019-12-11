#include "FloorSwitch.h"
#include "SoundManager.h"
#include "LaserGate.h"

FloorSwitch::FloorSwitch()
{
	delay = 5.0f;
	switchEntity = nullptr;

	startTimerTime = 0;
	bIsTimerSet = false;

	unpressedColor = Vec3(88/255.0f, 130/255.0f, 122/255.0f);
	pressedColor = Vec3(131 / 255.0f, 212 / 255.0f, 197 / 255.0f);

	timerSource = nullptr;
}

FloorSwitch::~FloorSwitch()
{
}

void FloorSwitch::Attach()
{
	switchEntity = entity->GetChild(0);
	switchEntity->SetCollisionType(Collision::None);
	switchEntity->SetMass(0);
	switchEntity->SetColor(unpressedColor.r, unpressedColor.g, unpressedColor.b);

	switchUnpressedPos = switchEntity->GetPosition(false);
	
	switchPressedPos = switchUnpressedPos - Vec3(0, 0.10f, 0);

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
	delay = String::Float(entity->GetKeyValue("delay"));
}

void FloorSwitch::UpdateWorld()
{
	PickInfo pickInfo;
	if (World::GetCurrent()->Pick(entity->GetPosition(true) - Vec3(0, 0.05f, 0), entity->GetPosition(true) + Vec3(0, 0.02f, 0), pickInfo, 0.0f, false, 11))
	{
		if (std::find(currentCollisions.begin(), currentCollisions.end(), pickInfo.entity) == currentCollisions.end())
		{
			currentCollisions.push_back(pickInfo.entity);
		}
	}

	if (bIsTimerSet)
	{
		float currentDelay = (Time::GetCurrent() - startTimerTime) / 1000.0f;
		if (currentDelay >= delay)
		{
			bIsTimerSet = false;
			if (switchEntity)
			{
				switchEntity->SetPosition(switchUnpressedPos);
				switchEntity->SetColor(unpressedColor.r, unpressedColor.g, unpressedColor.b);
			}
			for (LaserGate* laserGate : targets)
			{
				laserGate->ToggleGate();
				timerSource->Stop();
				SoundManager::Play("switchPress");
			}
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

void FloorSwitch::OnBeginCollision(Entity* otherEntity)
{
	if (bIsTimerSet) { return; }
	if (switchEntity)
	{
		switchEntity->SetPosition(switchPressedPos);
	}
	for (LaserGate* laserGate : targets)
	{
		laserGate->ToggleGate();
		switchEntity->SetColor(pressedColor.r, pressedColor.g, pressedColor.b);
	}
	SoundManager::Play("switchPress");
}

void FloorSwitch::OnEndCollision(Entity* otherEntity)
{
	bIsTimerSet = true;
	startTimerTime = Time::GetCurrent();
	timerSource = Source::Create();
	timerSource->SetLoopMode(true);
	timerSource->SetSound(SoundManager::LoadSound("timer"));
	timerSource->Play();
}
