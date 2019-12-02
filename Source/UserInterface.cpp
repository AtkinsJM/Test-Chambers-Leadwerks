#include "UserInterface.h"
#include "FadeScreen.h"

std::map<string, string> UserInterface::imageMap;

UserInterface::UserInterface()
{
	//create gui
	gui = GUI::Create(Context::GetCurrent());
	float guiScale = gui->GetScale();
	gui->GetBase()->SetScript("Scripts/GUI/Panel.lua");
	//make the base gui invisible if you want
	gui->GetBase()->SetObject("backgroundcolor", new Vec4(0, 0, 0, 0));

	fadeScreen = new FadeScreen(gui);

	activeWidgets = list<Widget*>();

	LoadImages();
}

UserInterface::~UserInterface()
{
	delete fadeScreen;
	delete gui;
}

void UserInterface::Process()
{
	fadeScreen->Process();
}

void UserInterface::Reset()
{
	fadeScreen->Reset();
	gui->Clear();
	for (auto widget : activeWidgets)
	{
		widget->Release();
	}
	activeWidgets.clear();
}

void UserInterface::LoadImages()
{
	imageMap["redKeySprite"] = "Sprites/Custom/red_key.tex";
	imageMap["blueKeySprite"] = "Sprites/Custom/blue_key.tex";
	imageMap["yellowKeySprite"] = "Sprites/Custom/yellow_key.tex";
	imageMap["greenKeySprite"] = "Sprites/Custom/green_key.tex";
	imageMap["orangeKeySprite"] = "Sprites/Custom/orange_key.tex";
	imageMap["purpleKeySprite"] = "Sprites/Custom/purple_key.tex";
}

void UserInterface::CreateImage(string imageKey, int x, int y, int width, int height)
{
	Image* image = gui->LoadImageA(imageMap[imageKey]);
	Widget* panel = Widget::Panel(x, y, width, height, gui->GetBase());
	activeWidgets.push_back(panel);
	panel->SetImage(image);
	image->Release();
	panel->SetObject("backgroundcolor", new Vec4(0, 0, 0, 0));
	panel->SetObject("border", false);
}

void UserInterface::FadeIn(float dur)
{
	fadeScreen->FadeIn(dur);
}

void UserInterface::FadeOut(float dur)
{
	fadeScreen->FadeOut(dur);
}
