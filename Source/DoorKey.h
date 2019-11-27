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

		const Vec4 BLUE_COLOUR = Vec4(0, 0.25f, 0.50f, 1.0f);
		const Vec4 RED_COLOUR = Vec4(0.81f, 0, 0, 1.0f);
		const Vec4 YELLOW_COLOUR = Vec4(0.91f, 0.91f, 0, 1.0f);
		const Vec4 GREEN_COLOUR = Vec4(0, 0.50f, 0, 1.0f);
		const Vec4 ORANGE_COLOUR = Vec4(1.0f, 0.50f, 0.25f, 1.0f);
		const Vec4 PURPLE_COLOUR = Vec4(0.50f, 0, 1.0f, 1.0f);
};