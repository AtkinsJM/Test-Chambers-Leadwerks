#include "LaserGate.h"

LaserGate::LaserGate()
{
}

LaserGate::~LaserGate()
{
}

void LaserGate::Attach()
{
	particleSystems.emplace_back(static_cast<Emitter*>(entity->FindChild("Particles_Top")));
	particleSystems.emplace_back(static_cast<Emitter*>(entity->FindChild("Particles_Middle")));
	particleSystems.emplace_back(static_cast<Emitter*>(entity->FindChild("Particles_Bottom")));

}

void LaserGate::UpdateWorld()
{
}
