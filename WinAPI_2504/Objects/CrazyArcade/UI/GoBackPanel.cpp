#include "Framework.h"
#include "GoBackPanel.h"

GoBackPanel::GoBackPanel()
{
	CreateButtons();
	CreateBackGround();
	SetEventFunc();
}

GoBackPanel::~GoBackPanel()
{
}

void GoBackPanel::CreateButtons()
{
	CreateButton(L"YesButton", Vector2(600, 450), Vector2(80, 50));
	CreateButton(L"NoButton", Vector2(800, 450), Vector2(80, 50));
}

void GoBackPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Back/backGround.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void GoBackPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickYesButton();});
	buttons[1]->SetOnClick([this]() {OnClickNoButton();});
}

void GoBackPanel::OnClickYesButton()
{
	SCENE->ChangeScene("Loby");
}

void GoBackPanel::OnClickNoButton()
{
	UIManager::Get()->PopForntPanel();
}
