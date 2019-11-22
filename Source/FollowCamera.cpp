#include "FollowCamera.h"

FollowCamera::FollowCamera(Entity* followEntity) : followEntity(followEntity), camera(nullptr)
{

	cameraOffset = Vec3(-10, 15, -10);
	cameraRot = Vec3(45, 45, 0);
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
	if (!followEntity || !camera) { return; }
	camera->SetPosition(followEntity->GetPosition(true) + cameraOffset);
}
