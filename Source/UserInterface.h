#pragma once
#include "Leadwerks.h"
#include <map>

using namespace Leadwerks;

class FadeScreen;

class UserInterface : public Actor
{
	public:
		UserInterface();
		~UserInterface();
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

		void LoadImages();

		void CreateImage(string imageKey, int x, int y, int width, int height);

		void FadeIn(float dur);
		void FadeOut(float dur);

	private:
		GUI* gui;
		static std::map<string, string> imageMap;

		list<Widget*> activeWidgets;

		FadeScreen* fadeScreen;
};
