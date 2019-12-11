#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class LaserGate;

class FloorSwitch : public Actor
{
	public:
		FloorSwitch();
		~FloorSwitch();
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
		
		void OnBeginCollision(Entity* otherEntity);

		void OnEndCollision(Entity* otherEntity);

	private:
		std::vector<LaserGate*> targets;

		float delay;

		Entity* switchEntity;

		Vec3 switchPressedPos;
		Vec3 switchUnpressedPos;

		float startTimerTime;
		bool bIsTimerSet;

		Vec3 unpressedColor;
		Vec3 pressedColor;

		Source* timerSource;

		vector<Entity*> collisionsLastFrame;
		vector<Entity*> currentCollisions;
};
