#include "Leadwerks.h"

using namespace Leadwerks;

class PlayerController : public Actor
{
	public:
		PlayerController();

		virtual void UpdatePhysics();

		virtual void Attach();

	private:
		Camera* mainCamera = nullptr;
		Vec3 cameraOffset;
		Vec3 cameraRot;
		Vec3 startPos;
};