#include "LaserGate.h"

LaserGate::LaserGate()
{
	bIsActive = true;
}

LaserGate::~LaserGate()
{
}

void LaserGate::Attach()
{
	particleSystems.emplace_back(static_cast<Emitter*>(entity->FindChild("Particles_Top")));
	particleSystems.emplace_back(static_cast<Emitter*>(entity->FindChild("Particles_Middle")));
	particleSystems.emplace_back(static_cast<Emitter*>(entity->FindChild("Particles_Bottom")));
	bIsActive = !entity->Hidden();
}

void LaserGate::UpdateWorld()
{
}

void LaserGate::ToggleGate()
{
	bIsActive = !bIsActive;

	if (bIsActive)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void LaserGate::Activate()
{
	entity->Show();
}

void LaserGate::Deactivate()
{
	entity->Hide();
}
