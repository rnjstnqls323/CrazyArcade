#include "Framework.h"

StorePanel::StorePanel()
{
	type = PanelType::StorePanel;
	CreateButtons();
	CreateBackGround();
	CreateShowLucci();
	SettingItem();
	CreateChoiceItem();
	testBackGround = new PlayerBackGround({930,550});


	SetEventFunc();


}

StorePanel::~StorePanel()
{
	for (Quad* quad : showLucci)
	{
		delete quad;
	}
	showLucci.clear();

	delete item;
	delete choiceItem;
}

void StorePanel::Update(Player* player)
{
	Panel::Update();

	item->Update();

	SavePreType();
	ChangeCoiceItem();
	if (player->GetLucci() == lucci) return;
	ChangeLucci(player->GetLucci());
}

void StorePanel::Render()
{
	Panel::Render();
	for (Quad* quad : showLucci)
	{
		quad->Render();
	}
	item->Render();

	choiceItem->Render();
	testBackGround->Render();
}

void StorePanel::Reset()
{
	isSavePreType = false;
	isChoice = false;

	preChoiceType.backGroundType = PlayerBackGroundType::Basic;
	preChoiceType.bubbleType = BubbleType::Basic;
	preChoiceType.shaShakType = ShaShakType::Basic;
	buyItem.status = ShowItemStatus::None;

}

void StorePanel::CreateButtons()
{
	CreateButton(L"OutButton", Vector2(300, 115), Vector2(180, 40));
	CreateButton(L"ExitButton", Vector2(1175, 115), Vector2(40, 30));
	CreateButton(L"BubbleButton", Vector2(300, 800), Vector2(100, 30));
	CreateButton(L"BackGroundButton", Vector2(410, 800), Vector2(100, 30));
	CreateButton(L"ShaShakButton", Vector2(520, 800), Vector2(100, 30));
	CreateButton(L"TestButton", Vector2{ 380,220 }, Vector2{ 150,40 });
	CreateButton(L"BuyButton", Vector2{ 650,220 }, Vector2{ 150,40 });
}

void StorePanel::CreateBackGround()
{
	backGround = new Quad(path + L"backGround.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void StorePanel::CreateShowLucci()
{
	showLucci.resize(8);
	Vector2 startPos = { 980,820 };
	float addX = 30;
	int count = 0;
	for (Quad*& quad : showLucci)
	{
		quad = new Quad(path + L"0.png");
		quad->SetLocalScale(1.2, 1.2);
		quad->SetParent(this);
		quad->SetLocalPosition(startPos.x + addX * count++, startPos.y);
		quad->UpdateWorld();
	}
}

void StorePanel::CreateChoiceItem()
{
	choiceItem = new Quad(path+L"Information.png");
	choiceItem->SetLocalPosition(Vector2(520, 300));
	choiceItem->SetParent(this);
	choiceItem->UpdateWorld();
}

void StorePanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickGoBack();});
	buttons[1]->SetOnClick([this]() {OnClickExit();});
	buttons[2]->SetOnClick([this]() {OnClickItem(ShowItemStatus::Bubble);});
	buttons[3]->SetOnClick([this]() {OnClickItem(ShowItemStatus::BackGround);});
	buttons[4]->SetOnClick([this]() {OnClickItem(ShowItemStatus::ShaShak);});
	buttons[5]->SetOnClick([this]() {OnClickTest();});
	buttons[6]->SetOnClick([this]() {OnClickSet();});

	EventManager::Get()->AddEvent("OutStore", [this](void* param) {ChangePreType(); });
}

void StorePanel::OnClickExit()
{
	UIManager::Get()->AddShowPanel(PanelType::ExitPanel);
}

void StorePanel::OnClickGoBack()
{
	UIManager::Get()->AddShowPanel(PanelType::GoBackPanel);
}

void StorePanel::OnClickItem(ShowItemStatus status)
{
	item->ChaingeCurStatus(status);
}

void StorePanel::OnClickTest()
{
	switch (item->GetCurStatus())
	{
	case ShowItemStatus::Bubble:
		BubbleManager::Get()->ChangeBubbleType(item->GetItemType().bubbleType);
		break;
	case ShowItemStatus::BackGround:
		PlayerBackGround::SetBackGroundType(item->GetItemType().backGroundType);
		break;
	case ShowItemStatus::ShaShak:
		ShaShak::SetShaShakType(item->GetItemType().shaShakType);
		break;
	}
}

void StorePanel::OnClickSet()
{
	if (!isChoice)
	{
		UIManager::Get()->AddShowPanel(PanelType::NoChoiceAlretPanel);
		return;
	}
	SetBuyItem();
	EventManager::Get()->ExcuteEvent("SendItemData", &buyItem);
	UIManager::Get()->AddShowPanel(PanelType::BuyCheckPanel);
}

void StorePanel::ChangeLucci(int lucci)
{
	this->lucci = lucci;

	int temp = lucci;
	int divisor = 10000000; 

	if (temp > 99999999)
	{
		for (int i = 0; i < 8; ++i) // 총 8자리
		{
			showLucci[i]->GetMaterial()->SetBaseMap(path + L"9.png");
		}
		return;
	}
	for (int i = 0; i < 8; ++i) // 총 8자리
	{
		int num = temp / divisor;
		if (num > 0 || i < showLucci.size()) // 숫자가 존재하거나 showLucci 범위 내
		{
			showLucci[i]->GetMaterial()->SetBaseMap(path + to_wstring(num) + L".png");
			temp %= divisor;
		}
		divisor /= 10;
	}

}

void StorePanel::ChangeCoiceItem()
{
	if (item->GetItemType().backGroundType == preChoiceType.backGroundType 
		&& item->GetItemType().bubbleType == preChoiceType.bubbleType
		&& item->GetItemType().shaShakType == preChoiceType.shaShakType) return;
	ShowItemStatus type = item->GetCurStatus();
	preChoiceType = item->GetItemType();
	wstring name;
	switch (type)
	{
	case ShowItemStatus::Bubble:
		name = L"bubble";
		name+=BubbleManager::Get()->GetBubbleTypeToWString(preChoiceType.bubbleType);
		break;
	case ShowItemStatus::BackGround:
		name = L"backGround";
		name += PlayerBackGround::GetBackGroundTypeToWString(preChoiceType.backGroundType);
		break;
	case ShowItemStatus::ShaShak:
		name = L"shaShak";
		name += ShaShak::GetShaShakTypeToWString(preChoiceType.shaShakType);
		break;
	}
	choiceItem->GetMaterial()->SetBaseMap(path+name+L".png");
	isChoice = true;
}

void StorePanel::ChangePreType()
{
	PlayerBackGround::SetBackGroundType(preType.backGroundType);
	BubbleManager::Get()->ChangeBubbleType(preType.bubbleType);
}

void StorePanel::SavePreType()
{
	if (isSavePreType) return;

	isSavePreType = true;
	preType.backGroundType = PlayerBackGround::GetBackGroundType();
	preType.bubbleType = BubbleManager::Get()->GetBubbleType();
	preType.shaShakType = ShaShak::GetShaShakType();
}

void StorePanel::SettingItem()
{
	item = new PlayerItem();
	item->SetLocalPosition(510, 550);
	item->ItemUpdateWorld();

	for (int i = 0;i < (int)BubbleType::RedPang;i++)
	{
		BubbleType type = (BubbleType)(i + 1);
		item->InsertBubble(type);
	}
	for (int i = 0;i < (int)PlayerBackGroundType::Hopi;i++)
	{
		PlayerBackGroundType type = (PlayerBackGroundType)(i + 1);
		item->InsertBackGround(type);
	}
	for (int i = 0; i < (int)ShaShakType::Heart; i++)
	{
		ShaShakType type = (ShaShakType)(i + 1);
		item->InsertShaShak(type);
	}
	preChoiceType = item->GetItemType();
}

void StorePanel::SetBuyItem()
{
	buyItem.status = item->GetCurStatus();
	buyItem.bubbleType = item->GetItemType().bubbleType;
	buyItem.backGroundType = item->GetItemType().backGroundType;
	buyItem.shaShakType = item->GetItemType().shaShakType;
}

