#include "FollowCamera.h"

FollowCamera::FollowCamera(Entity* followEntity) : followTarget(followEntity), camera(nullptr)
{

	cameraOffset = Vec3(-10, 15, -10);
	cameraRot = Vec3(45, 45, 0);
	followHeight = cameraOffset.y;
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
}

void FollowCamera::UpdateWorld()
{
	if (!followTarget || !camera) { return; }
	Vec3 desiredPosition = followTarget->GetPosition(true) + cameraOffset;
	// TODO allow for varing followHeight based on followTarget's elevation.
	camera->SetPosition(desiredPosition.x, followHeight, desiredPosition.z);
}
