#include "PlayerController.h"

PlayerController::PlayerController()
{
	startPos = Vec3(0, 3, 0);
	cameraOffset = Vec3(-10, 15, -10);
	cameraRot = Vec3(45, 45, 0);
}

void PlayerController::Attach()
{
	entity->SetPhysicsMode(Entity::CharacterPhysics);
	entity->SetPosition(startPos);
	entity->SetMass(1);
	Print("PlayerController attached to " + entity->GetClassNameA());

	Model* playerBox = Model::Box(entity);
	playerBox->SetPosition(0, (playerBox->GetScale().y) / 2, 0);

	mainCamera = Camera::Create(entity);
	
	mainCamera->SetRotation(cameraRot);
	mainCamera->SetPosition(cameraOffset);
	mainCamera->SetProjectionMode(Camera::Orthographic);
	mainCamera->SetZoom(50);
	//mainCamera->SetDebugPhysicsMode(true);
}

void PlayerController::UpdatePhysics()
{
}