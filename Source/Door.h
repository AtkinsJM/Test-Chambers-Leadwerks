#pragma once
#include "Leadwerks.h"
#include "DoorKeyType.h"

using namespace Leadwerks;

class Door : public Actor
{
	public:
		Door();
		~Door();
		virtual void Attach();
		//virtual void Detach();
		//virtual void UpdateWorld();
		//virtual void UpdateMatrix();
		//virtual void UpdatePhysics();
		//virtual void Wake();
		//virtual void Sleep();
		//virtual void Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed);
		//virtual void PostRender();
		//virtual void Draw();
		//virtual void DrawEach(Camera* camera);
		//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);

		void Unlock();

		FORCEINLINE DoorKeyType GetRequiredKeyType() { return requiredKeyType; }
	
	private:
		DoorKeyType requiredKeyType;
};