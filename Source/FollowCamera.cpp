#include "FollowCamera.h"

FollowCamera::FollowCamera(Entity* followEntity) : followTarget(followEntity), camera(nullptr)
{

	cameraOffset = Vec3(-10, 15, -10);
	cameraRot = Vec3(45, 45, 0);
	followHeight = cameraOffset.y;
	movementSpeed = 5;
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Attach()
{
	camera = static_cast<Camera*>(entity);
	if (!camera) { return; }
	camera->SetRotation(cameraRot);
	camera->SetPosition(cameraOffset);
	camera->SetProjectionMode(Camera::Orthographic);
	camera->SetZoom(50);
	camera->SetGravityMode(false);
	camera->SetMass(1);
}

void FollowCamera::UpdateWorld()
{
	if (!followTarget || !camera) { return; }
	Vec3 desiredPosition = followTarget->GetPosition(true) + cameraOffset;
	desiredPosition.y = followHeight;
	
	// TODO allow for varing followHeight based on followTarget's elevation.
	//camera->SetPosition(desiredPosition.x, followHeight, desiredPosition.z);
	Vec3 movementVector = desiredPosition - camera->GetPosition();
	camera->SetVelocity((movementVector.Length() > 0.1f) ? movementVector * movementSpeed : Vec3(0,0,0), true);
}
