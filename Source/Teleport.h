#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class Teleport : public Actor
{
	public:
		Teleport();
		~Teleport();
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

		void BeginTeleport(Entity* otherEntity);

		void OnBeginCollision(Entity* otherEntity);

		void OnEndCollision(Entity* otherEntity);

	private:
		bool bIsTeleporting;

		Vec3 destination;

		Entity* target;

		float delay;
		float startTeleportTime;

		vector<Entity*> collisionsLastFrame;
		vector<Entity*> currentCollisions;
};