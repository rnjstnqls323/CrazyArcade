#include "Framework.h"

ExitPanel::ExitPanel()
{
	CreateButtons();
	CreateBackGround();
	SetEventFunc();
}

ExitPanel::~ExitPanel()
{
}

void ExitPanel::CreateButtons()
{
	CreateButton(L"YesButton", Vector2(600, 450), Vector2(80, 50));
	CreateButton(L"NoButton", Vector2(800, 450), Vector2(80, 50));
}

void ExitPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Exit/backGround.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void ExitPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() { OutButton(); });
	buttons[1]->SetOnClick([this]() { BackButton(); });
}

void ExitPanel::BackButton()
{
	UIManager::Get()->PopForntPanel();
}
void ExitPanel::OutButton()
{
	exit(0);
}
