#include "Framework.h"

NoChoiceAlretPanel::NoChoiceAlretPanel()
{
	type = PanelType::NoChoiceAlretPanel;
	CreateButtons();
	CreateBackGround();

	SetEventFunc();
}

NoChoiceAlretPanel::~NoChoiceAlretPanel()
{
}

void NoChoiceAlretPanel::CreateButtons()
{
	CreateButton(L"YesButton", { 500,450 }, { 80,30 });
}

void NoChoiceAlretPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/NoChoiceItem/backGround.png");
	backGround->SetParent(this);
	backGround->SetLocalPosition({ 500,500 });
	backGround->UpdateWorld();
}

void NoChoiceAlretPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickYes();});
}

void NoChoiceAlretPanel::OnClickYes()
{
	UIManager::Get()->PopForntPanel();
}
