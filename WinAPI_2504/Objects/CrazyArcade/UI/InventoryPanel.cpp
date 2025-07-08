#include "Framework.h"

InventoryPanel::InventoryPanel()
{
	type = PanelType::InventoryPanel;
	CreateButtons();
	CreateBackGround();
	CreateShowSetItem();


	itemPanel = new PlayerItem;
	itemPanel->SetParent(this);

	SetEventFunc();
}

InventoryPanel::~InventoryPanel()
{
	delete itemPanel;

	for (int i = 0; i < (int)ShowItemStatus::ShaShak; i++)
	{
		ShowItemStatus type = (ShowItemStatus)(i + 1);
		delete showSetItem[type].back;
		delete showSetItem[type].front;
	}
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
	Vector2 startPos = {600,280};
	float addX = 100;
	for (int i=0;i< (int)ShowItemStatus::ShaShak;i++)                                       
	{
		ShowItemStatus type = (ShowItemStatus)(i + 1);
		wstring name = itemPanel->GetShowItemStatusToWString(type);
		showSetItem[type].back = new Quad(path + name + L"/backGround.png");
		showSetItem[type].front = new Quad(path + name + L"/basic.png");
		showSetItem[type].back->SetParent(this);
		showSetItem[type].front->SetParent(this);
		showSetItem[type].back->SetLocalPosition(startPos.x+addX*i,startPos.y);
		showSetItem[type].front->SetLocalPosition(startPos.x + addX * i, startPos.y);
		showSetItem[type].back->UpdateWorld();
		showSetItem[type].front->UpdateWorld();
	}
}

void InventoryPanel::ChangeShowItemFront(ShowItemStatus type)
{
	wstring item = L"/";
	switch (type)
	{
	case ShowItemStatus::Bubble:
		item += BubbleManager::Get()->GetBubbleTypeToWString(BubbleManager::Get()->GetBubbleType());
		break;
	case ShowItemStatus::BackGround:
		item += PlayerBackGround::GetBackGroundTypeToWString(PlayerBackGround::GetBackGroundType());
		break;
	case ShowItemStatus::ShaShak:
		item += ShaShak::GetShaShakTypeToWString(ShaShak::GetShaShakType());
	}
	wstring name = itemPanel->GetShowItemStatusToWString(type);

	 showSetItem[type].front->GetMaterial()->SetBaseMap(path + name + item + L".png");
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
	buttons[3]->SetOnClick([this]() {OnClickItemButton(ShowItemStatus::ShaShak);});
	buttons[4]->SetOnClick([this]() {OnClickItemSetting();});
	buttons[4]->SetClickSound("ef_Set");
	buttons[5]->SetOnClick([this]() {OnClickItemSetOff();});
	buttons[5]->SetClickSound("ef_Set");

	EventManager::Get()->AddEvent("BuyItem", [this](void* param) {AddItem((BuyItem*)param);});
}

void InventoryPanel::OnClickCloseButton()
{
	UIManager::Get()->PopForntPanel();
}

void InventoryPanel::OnClickItemButton(ShowItemStatus status)
{
	itemPanel->SetBasic(status);
	itemPanel->ChaingeCurStatus(status);
}

void InventoryPanel::OnClickItemSetting()
{
	ShowItemStatus status = itemPanel->GetCurStatus();
	ChoiceItemType type = itemPanel->GetItemType();
	switch (status)
	{
	case ShowItemStatus::Bubble:
		BubbleManager::Get()->ChangeBubbleType(type.bubbleType);
		ChangeShowItemFront(ShowItemStatus::Bubble);
		break;
	case ShowItemStatus::BackGround:
		PlayerBackGround::SetBackGroundType(type.backGroundType);
		ChangeShowItemFront(ShowItemStatus::BackGround);
		break;
	case ShowItemStatus::ShaShak:
		ShaShak::SetShaShakType(type.shaShakType);
		ChangeShowItemFront(ShowItemStatus::ShaShak);
		break;
	}

}

void InventoryPanel::OnClickItemSetOff()
{
	ShowItemStatus status = itemPanel->GetCurStatus();
	if (status == ShowItemStatus::None)
	{
		BubbleManager::Get()->ChangeBubbleType(BubbleType::Basic);
		PlayerBackGround::SetBackGroundType(PlayerBackGroundType::Basic);
		ShaShak::SetShaShakType(ShaShakType::Basic);
		return;
	}
	itemPanel->SetBasic(status);
	switch (status)
	{
	case ShowItemStatus::None:
		return;
	case ShowItemStatus::Bubble:
		BubbleManager::Get()->ChangeBubbleType(BubbleType::Basic);
		ChangeShowItemFront(ShowItemStatus::Bubble);
		break;
	case ShowItemStatus::BackGround:
		PlayerBackGround::SetBackGroundType(PlayerBackGroundType::Basic);
		ChangeShowItemFront(ShowItemStatus::BackGround);
		break;
	case ShowItemStatus::ShaShak:
		ShaShak::SetShaShakType(ShaShakType::Basic);
		ChangeShowItemFront(ShowItemStatus::ShaShak);
	}
}

void InventoryPanel::AddItem(BuyItem* item)
{
	if (Player::GetLucci() < 10000)
	{
		UIManager::Get()->AddShowPanel(PanelType::NoLucciAlretPanel);
		return;
	}

	bool isInsert = false;
	switch (item->status)
	{
	case ShowItemStatus::BackGround:
		isInsert = itemPanel->InsertBackGround(item->backGroundType);
		break;
	case ShowItemStatus::Bubble:
		isInsert = itemPanel->InsertBubble(item->bubbleType);
		break;
	case ShowItemStatus::ShaShak:
		isInsert = itemPanel->InsertShaShak(item->shaShakType);
		break;
	}
	
	if (!isInsert)
	{
		UIManager::Get()->AddShowPanel(PanelType::InventoryCheckAlretPanel);
		return;
	}
	Player::SetLucci(Player::GetLucci() - 5000);
}

