#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class Portal : public Actor
{
public:
	Portal();
	~Portal();
	virtual void Attach();
	//virtual void Detach();
	virtual void UpdateWorld();
	//virtual void UpdateMatrix();
	//virtual void UpdatePhysics();
	//virtual void Wake();
	//virtual void Sleep();
	virtual void Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed);
	//virtual void PostRender();
	//virtual void Draw();
	//virtual void DrawEach(Camera* camera);
	//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);

	void BeginTeleport();

	void OnBeginCollision(Entity* otherEntity);

	void OnEndCollision(Entity* otherEntity);

private:
	// TODO: change vairable name
	bool bIsTeleporting;
	
	float delay;
	float startTeleportTime;

	int destinationKey;

	vector<Entity*> collisionsLastFrame;
	vector<Entity*> currentCollisions;
};