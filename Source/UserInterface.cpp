#include "UserInterface.h"

std::map<string, string> UserInterface::imageMap;

UserInterface::UserInterface()
{
	
}

UserInterface::~UserInterface()
{
	gui->Release();
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
	// TODO create single gui, rather than one per image
	// TODO consider whether class should be static, or instanced by the app and passed to the GameManager?
	//create gui
	GUI*  gui = GUI::Create(Context::GetCurrent());
	float guiScale = gui->GetScale();
	gui->GetBase()->SetScript("Scripts/GUI/Panel.lua");
	//make the base gui invisible if you want
	gui->GetBase()->SetObject("backgroundcolor", new Vec4(0, 0, 0, 0));
	Image* image = gui->LoadImageA(imageMap[imageKey]);
	Widget* panel = Widget::Panel(x, y, width, height, gui->GetBase());
	panel->SetImage(image);
	panel->SetObject("backgroundcolor", new Vec4(0, 0, 0, 0));
	panel->SetObject("border", false);
}
