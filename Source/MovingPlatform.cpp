#include "MovingPlatform.h"
#include "PlayerController.h"

MovingPlatform::MovingPlatform()
{
	bIsTransporting = false;
	bIsMoving = false;
	target = nullptr;
	startTransportTime = 0;
	delay = 0.5f;

	currentWaypointIndex = 0;
	sliderJoint = nullptr;
	speed = 1.0f;

	platform = nullptr;
}

MovingPlatform::~MovingPlatform()
{
}

void MovingPlatform::Attach()
{
	entity->SetGravityMode(false);
	entity->SetMass(-1);
	entity->SetSweptCollisionMode(true);
	platform = entity->GetChild(0);
	platform->SetMass(0);

	int numWaypoints = String::Int(entity->GetKeyValue("numWaypoints"));
	Vec3 startPos = entity->GetPosition(true);
	waypoints.push_back(startPos);

	if (numWaypoints > 0)
	{
		for (int i = 1; i <= numWaypoints; i++)
		{
			string keyName = "waypoint" + String(i);
			if (entity->GetKeyValue(keyName) != "")
			{
				Entity* waypoint = World::GetCurrent()->FindEntity(entity->GetKeyValue(keyName));
				if (waypoint)
				{
					waypoints.push_back(waypoint->GetPosition(true));
				}
			}
		}
	}
	speed = String::Float(entity->GetKeyValue("speed"));

	// Set up initial slider to hold entity in place
	sliderJoint = Joint::Slider(startPos.x, startPos.y, startPos.z, 0, 0, 0, entity, nullptr);
	sliderJoint->EnableMotor();
	sliderJoint->SetAngle(0);
}

void MovingPlatform::UpdateWorld()
{
	if (waypoints.size() == 0) { return; }

	if (bIsTransporting)
	{
		if (!bIsMoving)
		{
			float currentDelay = (Time::GetCurrent() - startTransportTime) / 1000.0f;
			if (currentDelay >= delay)
			{
				Transport();
			}
		}
		else
		{
			target->SetPosition(targetRelativePos, false);
			float distance = (entity->GetPosition() - waypoints[currentWaypointIndex]).Length();
			if (distance < 0.02f && waypoints.size() > 1)
			{
				entity->SetPosition(waypoints[currentWaypointIndex]);
				target->SetPosition(targetRelativePos, false);
				bIsMoving = false;
				bIsTransporting = false;
				PlayerController* player = static_cast<PlayerController*>(target->GetActor());
				if (player)
				{
					player->ToggleIsBeingTransported();
				}
				target->SetParent(nullptr);
				target = nullptr;
			}
		}
	}
}

void MovingPlatform::Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed)
{
	if (!bIsTransporting)
	{
		PlayerController* player = static_cast<PlayerController*>(otherEntity->GetActor());
		if (player)
		{
			if (Math::Abs(player->GetTargetPosition().x - entity->GetPosition().x) <= 0.01f && Math::Abs(player->GetTargetPosition().z - entity->GetPosition().z) <= 0.01f)
			{
				player->ToggleIsBeingTransported();
				BeginTransportation(otherEntity);
			}	
		}
	}
}

void MovingPlatform::BeginTransportation(Entity* otherEntity)
{
	bIsTransporting = true;
	target = otherEntity;
	target->SetParent(entity);
	startTransportTime = Time::GetCurrent();
}

void MovingPlatform::Transport()
{
	if (!target) { return; }
	targetRelativePos = target->GetPosition(false);
	currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
	Vec3 newWaypoint = waypoints[currentWaypointIndex];
	Vec3 movementVector = (entity->GetPosition() - newWaypoint);
	float distance = movementVector.Length();

	// Remove the old slider joint
	if (sliderJoint)
	{
		sliderJoint->DisableMotor();
		sliderJoint->Release();
	}
	// Set up a new slider joint
	sliderJoint = Joint::Slider(newWaypoint.x, newWaypoint.y, newWaypoint.z, movementVector.x, movementVector.y, movementVector.z, entity, nullptr);
	sliderJoint->EnableMotor();
	sliderJoint->SetMotorSpeed(speed);
	sliderJoint->SetAngle(-distance);

	bIsMoving = true;
}
