#include "FollowCamera.h"

FollowCamera::FollowCamera(Entity* followEntity) : followTarget(followEntity), camera(nullptr)
{

	cameraOffset = Vec3(70, 70, -70);
	cameraRot = Vec3(35, -45, 0);
	followHeight = cameraOffset.y;
	targetHeight = followEntity->GetAABB().size.y;
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
	camera->SetPosition(followTarget->GetPosition(true) + cameraOffset);
	camera->SetProjectionMode(Camera::Orthographic);
	camera->SetZoom(50);
	//camera->SetFOV(8);
	camera->SetGravityMode(false);
	camera->SetMass(1);
	camera->SetClearColor(0.15f, 0.15f, 0.15f);
}

void FollowCamera::UpdateWorld()
{
	if (!followTarget || !camera) { return; }
	Vec3 desiredPosition = followTarget->GetPosition(true) + cameraOffset;
	desiredPosition.y = followHeight + targetHeight/2.0f;
	
	Vec3 movementVector = desiredPosition - camera->GetPosition();
	camera->SetVelocity((movementVector.Length() > 0.1f) ? movementVector * movementSpeed : Vec3(0,0,0), true);
}
