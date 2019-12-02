#pragma once
#include "Leadwerks.h"
#include "DoorKeyType.h"

using namespace Leadwerks;

class DoorKey;

class KeyManager : public Actor
{
	public:
		KeyManager();
		~KeyManager();
		//virtual void Attach();
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

		void PickUpDoorKey(DoorKey* doorKey);

		bool HasDoorKey(DoorKeyType doorKeyType);

	private:

		int doorKeySequence;

		int keysPickedUp;
};
