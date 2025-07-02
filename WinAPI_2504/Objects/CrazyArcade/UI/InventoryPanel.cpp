#include "Framework.h"

InventoryPanel::InventoryPanel()
{
	CreateButtons();
	CreateBackGround();

	SetEventFunc();

	itemPanel = new PlayerItem;
	itemPanel->SetParent(this);

	itemPanel->InsertBackGround(PlayerBackGroundType::Hopi);
	itemPanel->InsertBackGround(PlayerBackGroundType::Dragon);
	itemPanel->InsertBackGround(PlayerBackGroundType::Clover);
	itemPanel->InsertBackGround(PlayerBackGroundType::Cute);
	itemPanel->InsertBackGround(PlayerBackGroundType::Gold);
}

InventoryPanel::~InventoryPanel()
{
	delete itemPanel;
}

void InventoryPanel::Update(Player* player)
{
	Panel::Update();
	itemPanel->Update();
}

void InventoryPanel::Render()
{
	Panel::Render();
	itemPanel->Render();
	for (auto& item : showSetItem)
	{
		item.second.back->Render();
		item.second.front->Render();
	}
}

void InventoryPanel::CreateShowSetItem()
{
	for (int i=0;i< (int)ShowItemStatus::ShaShak+1;i++)                                       
	{
		ShowItemStatus type = (ShowItemStatus)(i + 1);
		wstring name = itemPanel->GetShowItemStatusToWString((ShowItemStatus)i); //스태틱으로 안빼도되겠지?
		showSetItem[(ShowItemStatus)i].back = new Quad(path + name + L"/backGround.png");
		showSetItem[(ShowItemStatus)i].front = new Quad(path + name + L"/basic.png");

		
	}
}

void InventoryPanel::CreateButtons()
{
	CreateButton(L"CloseButton", Vector2{ 950,760 }, Vector2{ 50,40 });
	CreateButton(L"BubbleButton", Vector2{ 480,760 }, Vector2{ 100,30 });
	CreateButton(L"BackGroundButton", Vector2{ 585,760 }, Vector2{ 100,30 });
	CreateButton(L"ShaShakButton", Vector2{ 690,760 }, Vector2{ 100,30 });
	CreateButton(L"ItemSettingButton", Vector2{ 590,220 }, Vector2{ 150,40 });
	CreateButton(L"ItemSetOffButton", Vector2{ 780,220 }, Vector2{ 150,40 });
}

void InventoryPanel::CreateBackGround()
{
	backGround = new Quad(path+L"Inventory.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void InventoryPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickCloseButton();});
	buttons[1]->SetOnClick([this]() {OnClickItemButton(ShowItemStatus::Bubble);});
	buttons[2]->SetOnClick([this]() {OnClickItemButton(ShowItemStatus::BackGround);});
	buttons[3]->SetOnClick([this]() {OnClickItemButton(ShowItemStatus::None);});
	buttons[4]->SetOnClick([this]() {OnClickItemSetting();});
	buttons[5]->SetOnClick([this]() {OnClickItemSetOff();});
}

void InventoryPanel::OnClickCloseButton()
{
	UIManager::Get()->PopForntPanel();
}

void InventoryPanel::OnClickItemButton(ShowItemStatus status)
{
	itemPanel->SetBasic();
	itemPanel->ChaingeCurStatus(status);
}

void InventoryPanel::OnClickItemSetting()
{
	ShowItemStatus status = itemPanel->GetCurStatus();
	ChoiceItemType type = itemPanel->GetItemType();
	switch (status)
	{
	case ShowItemStatus::None:
		return;
	case ShowItemStatus::Bubble:
		break;
	case ShowItemStatus::BackGround:
		PlayerBackGround::SetBackGroundType(type.backGroundType);
		break;
	}

}

void InventoryPanel::OnClickItemSetOff()
{
	itemPanel->SetBasic();
	ShowItemStatus status = itemPanel->GetCurStatus();
	ChoiceItemType type = itemPanel->GetItemType();
	switch (status)
	{
	case ShowItemStatus::None:
		return;
	case ShowItemStatus::Bubble:
		break;
	case ShowItemStatus::BackGround:
		PlayerBackGround::SetBackGroundType(type.backGroundType);
		break;
	}
}
