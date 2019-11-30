#include "FadeScreen.h"
#include "App.h"

FadeScreen::FadeScreen()
{
	//
	//create gui
	gui = GUI::Create(Context::GetCurrent());
	float guiScale = gui->GetScale();
	gui->GetBase()->SetScript("Scripts/GUI/Panel.lua");
	//make the base gui invisible if you want
	gui->GetBase()->SetObject("backgroundcolor", new Vec4(0, 0, 0, 0));

	panel = Widget::Panel(0, 0, Window::GetCurrent()->GetWidth(), Window::GetCurrent()->GetHeight(), gui->GetBase());

	color = Vec3(0.15f, 0.15f, 0.15f);
}

FadeScreen::~FadeScreen()
{
	panel->Release();
	gui->Release();
}


void FadeScreen::Process()
{
	if (bIsFading)
	{
		currentFadeTime = (Time::GetCurrent() - fadeStartTime) / 1000.0f;
		Print("Current time: " + String(Time::GetCurrent()));
		Print("Current fade time: " + String(currentFadeTime));
		float completion = currentFadeTime / duration;
		Print(completion);
		float newAlpha = Math::Clamp(Math::Lerp(1 - targetAlpha, targetAlpha, completion), 0, 1);
		Print(newAlpha);
		panel->SetObject("backgroundcolor", new Vec4(color.r, color.g, color.b, newAlpha));
		if (completion >= 1.0f)
		{
			Print("Finished fading");
			bIsFading = false;
		}
	}
}

void FadeScreen::FadeIn(float dur)
{
	bIsFading = true;
	currentAlpha = 1;
	targetAlpha = 0;
	duration = dur;
	fadeStartTime = Time::GetCurrent();
	Print("Start fading at: " + String(fadeStartTime));
}

void FadeScreen::FadeOut(float dur)
{
	bIsFading = true;
	currentAlpha = 0;
	targetAlpha = 1;
	duration = dur;
	fadeStartTime = Time::GetCurrent();
}


