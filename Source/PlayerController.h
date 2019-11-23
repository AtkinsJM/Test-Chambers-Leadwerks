#include "Leadwerks.h"

using namespace Leadwerks;

class PlayerController : public Actor
{
	public:
		PlayerController();
		~PlayerController();
		virtual void Attach();
		//virtual void Detach();
		virtual void UpdateWorld();
		//virtual void UpdateMatrix();
		virtual void UpdatePhysics();
		//virtual void Wake();
		//virtual void Sleep();
		//virtual void Collision(Entity* entity, const Vec3& position, const Vec3& normal, float speed);
		//virtual void PostRender();
		//virtual void Draw();
		//virtual void DrawEach(Camera* camera);
		//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);
		void StartRolling(Vec3 rotationPoint);
		void Roll();

	private:
		Vec3 forwardRotationPoint, backRotationPoint, leftRotationPoint, rightRotationPoint;
		float width;
		float rotationSpeed;

		Window* window;

		bool bIsRolling;

		float rotationAngle;
		Vec3 rotationOrigin;

		Vec3 relativePos;

		Vec3 rollingDirection;


		float distanceFromOrigin;
};