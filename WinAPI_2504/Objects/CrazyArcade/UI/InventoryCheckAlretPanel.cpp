#include "Framework.h"

InventoryCheckAlretPanel::InventoryCheckAlretPanel()
{
	type = PanelType::InventoryCheckAlretPanel;
	CreateButtons();
	CreateBackGround();

	SetEventFunc();
}

InventoryCheckAlretPanel::~InventoryCheckAlretPanel()
{
}

void InventoryCheckAlretPanel::CreateButtons()
{
	CreateButton(L"YesButton", { 500,450 }, { 80,30 });
}

void InventoryCheckAlretPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/InventoryCheckAlret/backGround.png");
	backGround->SetParent(this);
	backGround->SetLocalPosition({ 500,500 });
	backGround->UpdateWorld();
}

void InventoryCheckAlretPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickYes();});
}

void InventoryCheckAlretPanel::OnClickYes()
{
	UIManager::Get()->PopForntPanel();
}
