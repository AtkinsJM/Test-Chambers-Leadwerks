#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class MovingPlatform : public Actor
{
	public:
		MovingPlatform();
		~MovingPlatform();
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

		void BeginTransportation(Entity* otherEntity);

		void Transport();

		void OnBeginCollision(Entity* otherEntity);

		void OnEndCollision(Entity* otherEntity);

	private:
		Entity* target;

		Vec3 targetRelativePos;
		bool bIsTransporting;
		bool bIsMoving;

		float startTransportTime;

		float delay;
		
		std::vector<Vec3> waypoints;
		int currentWaypointIndex;

		float speed;

		Joint* sliderJoint;
		
		vector<Entity*> collisionsLastFrame;
		vector<Entity*> currentCollisions;
};
