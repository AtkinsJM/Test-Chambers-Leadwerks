#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class App;

class FadeScreen : public Actor
{
	public:
		FadeScreen();
		~FadeScreen();
		//virtual void Attach();
		//virtual void Detach();
		//virtual void UpdateWorld();
		//virtual void UpdateMatrix();
		//virtual void UpdatePhysics();
		//virtual void Wake();
		//virtual void Sleep();
		//virtual void Collision(Entity* otherEntity, const Vec3& position, const Vec3& normal, float speed);
		//virtual void PostRender();
		//virtual void Draw();
		//virtual void DrawEach(Camera* camera);
		//virtual void ReceiveSignal(const std::string& inputname, Entity* sender);
		virtual void Process();
		virtual void Reset();

		void FadeIn(float dur);
		void FadeOut(float dur);

	private:
		//App* app;
		GUI* gui;

		Widget* panel;

		float targetAlpha;
		float duration;

		float fadeStartTime;

		bool bIsFading;

		Vec3 color;
		float currentAlpha;

		float currentFadeTime;

		bool bInitialFade;
		float resetTime;
};