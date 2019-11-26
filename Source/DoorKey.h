#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

enum class DoorKeyType
{
	BLUE_KEY = 1,
	RED_KEY = 2,
	YELLOW_KEY = 4,
	GREEN_KEY = 8,
	ORANGE_KEY = 16,
	PURPLE_KEY = 32
};

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

};