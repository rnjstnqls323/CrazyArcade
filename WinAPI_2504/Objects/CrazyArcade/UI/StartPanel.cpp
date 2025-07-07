#include "Framework.h"

StartPanel::StartPanel()
{
	CreateButtons();
	CreateBackGround();

	SetEventFunc();
}

StartPanel::~StartPanel()
{
}

void StartPanel::CreateButtons()
{
	CreateButton(L"MapEditButton", { 500,230 }, { 300,100 });
	CreateButton(L"StartButton", { 900,230 }, { 300,100 });
}

void StartPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Start/backGround.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void StartPanel::OnClickMapEdit()
{
	SCENE->ChangeScene("Edit");
}

void StartPanel::OnClickStart()
{
	SCENE->ChangeScene("Loby");
}

void StartPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickMapEdit();});
	buttons[1]->SetOnClick([this]() {OnClickStart();});
}
