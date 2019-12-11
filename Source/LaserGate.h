#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class LaserGate : public Actor
{
	public:
		LaserGate();
		~LaserGate();
		virtual void Attach();
		//virtual void Detach();
		virtual void UpdateWorld();
		//virtual void UpdateMatrix();
		//virtual void UpdatePhysics();
		//virtual void Wake();
		//virtual void Sleep();
		//virtual void Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed);
		//virtual void PostRender();
		//virtual void Draw();
		//virtual void DrawEach(Camera* camera);
		//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);

		void ToggleGate();

		void Activate();
		void Deactivate();

	private:
		std::vector<Emitter*> particleSystems;

		bool bIsActive;
		
};
