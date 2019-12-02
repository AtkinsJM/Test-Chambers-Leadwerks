#include "FadeScreen.h"
#include "App.h"

FadeScreen::FadeScreen(GUI* gui) : gui(gui)
{
	panel = Widget::Panel(0, 0, Window::GetCurrent()->GetWidth(), Window::GetCurrent()->GetHeight(), gui->GetBase());

	color = Vec3(0.15f, 0.15f, 0.15f);

	targetAlpha = 0;
	duration = 0;

	fadeStartTime = 0;

	currentFadeTime = 0;

	resetTime = 0;

	bInitialFade = false;
	bIsFading = false;
}

FadeScreen::~FadeScreen()
{
	panel->Release();
	gui->Release();
}

void FadeScreen::Process()
{
	// Delay before fading in on level load to allow for other processes.
	if (bInitialFade && (Time::GetCurrent() - resetTime > 0.5f))
	{
		bInitialFade = false;
		FadeIn(0.5f);
	}
	// Lerp alpha value and assign color to panel
	if (bIsFading)
	{
		currentFadeTime = (Time::GetCurrent() - fadeStartTime) / 1000.0f;
		float completion = currentFadeTime / duration;
		float newAlpha = Math::Clamp(Math::Lerp(1 - targetAlpha, targetAlpha, completion), 0, 1);
		panel->SetObject("backgroundcolor", new Vec4(color.r, color.g, color.b, newAlpha));
		if (completion >= 1.0f)
		{
			bIsFading = false;
		}
	}
}

void FadeScreen::Reset()
{
	bInitialFade = true;
	resetTime = Time::GetCurrent();
}

void FadeScreen::FadeIn(float dur)
{
	bIsFading = true;
	targetAlpha = 0;
	duration = dur;
	fadeStartTime = Time::GetCurrent();
}

void FadeScreen::FadeOut(float dur)
{
	bIsFading = true;
	targetAlpha = 1;
	duration = dur;
	fadeStartTime = Time::GetCurrent();
}