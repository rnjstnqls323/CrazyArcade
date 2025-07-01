#include "Framework.h"

InventoryPanel::InventoryPanel()
{
	CreateBackGround();
}

InventoryPanel::~InventoryPanel()
{
}

void InventoryPanel::CreateButtons()
{
}

void InventoryPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Inventory/Inventory.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void InventoryPanel::SetEventFunc()
{
}
