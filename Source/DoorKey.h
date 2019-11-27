#pragma once
#include "Leadwerks.h"
#include "DoorKeyType.h"

using namespace Leadwerks;


class DoorKey : public Actor
{
	public:
		DoorKey();
		~DoorKey();
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

		void Destroy();

		FORCEINLINE DoorKeyType GetDoorKeyType() { return doorKeyType; }

	private:
		Vec3 startPosition;

		float amplitude;
		float frequency;
		float rotationSpeed;

		bool bFloats;
		bool bRotates;

		float recordedTime;

		DoorKeyType doorKeyType;

		Entity* parent;
		Entity* model;
};