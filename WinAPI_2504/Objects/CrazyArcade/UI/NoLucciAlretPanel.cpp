#include "Framework.h"

NoLucciAlretPanel::NoLucciAlretPanel()
{
	type = PanelType::NoLucciAlretPanel;
	CreateButtons();
	CreateBackGround();

	SetEventFunc();
}

NoLucciAlretPanel::~NoLucciAlretPanel()
{
}

void NoLucciAlretPanel::CreateButtons()
{
	CreateButton(L"YesButton", { 500,450 }, { 80,30 });
}

void NoLucciAlretPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/NoLucciAlret/backGround.png");
	backGround->SetParent(this);
	backGround->SetLocalPosition({ 500,500 });
	backGround->UpdateWorld();
}

void NoLucciAlretPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickYes();});
}

void NoLucciAlretPanel::OnClickYes()
{
	UIManager::Get()->PopForntPanel();
}
