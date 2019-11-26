#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

enum DoorKeyType
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

		Entity* parent;

		const Vec4 BLUE_COLOUR = Vec4(0, 64, 128, 255);
		const Vec4 RED_COLOUR = Vec4(206, 0, 0, 255);
		const Vec4 YELLOW_COLOUR = Vec4(232, 232, 0, 255);
		const Vec4 GREEN_COLOUR = Vec4(0, 128, 0, 255);
		const Vec4 ORANGE_COLOUR = Vec4(255, 128, 64, 255);
		const Vec4 PURPLE_COLOUR = Vec4(128, 0, 255, 255);
};