#pragma once

#include "Leadwerks.h"

using namespace Leadwerks;

class FollowCamera : public Actor
{
	public:
		FollowCamera(Entity* followEntity);
		~FollowCamera();
		virtual void Attach();
		//virtual void Detach();
		virtual void UpdateWorld();
		//virtual void UpdateMatrix();
		//virtual void UpdatePhysics();
		//virtual void Wake();
		//virtual void Sleep();
		//virtual void Collision(Entity* entity, const Vec3& position, const Vec3& normal, float speed);
		//virtual void PostRender();
		//virtual void Draw();
		//virtual void DrawEach(Camera* camera);
		//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);


		Camera* camera;
		Entity* followEntity;
	private:
		Vec3 cameraOffset;
		Vec3 cameraRot;
};