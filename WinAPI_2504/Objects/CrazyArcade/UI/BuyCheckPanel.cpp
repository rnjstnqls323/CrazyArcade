#include "Framework.h"

BuyCheckPanel::BuyCheckPanel()
{
	CreateButtons();
	CreateBackGround();

	SetEventFunc();
}

BuyCheckPanel::~BuyCheckPanel()
{
}

void BuyCheckPanel::CreateButtons()
{
	CreateButton(L"YesButton", { 420,450 }, { 100,50 });
	CreateButton(L"NoButton", { 570,450 }, { 100,50 });
}

void BuyCheckPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/BuyCheck/backGround.png");
	backGround->SetParent(this);
	backGround->SetLocalPosition({500,500});
	backGround->UpdateWorld();
}

void BuyCheckPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickYes(); });
	buttons[1]->SetOnClick([this]() {OnClickNo(); });
}

void BuyCheckPanel::OnClickYes()
{
	EventManager::Get()->ExcuteEvent("BuyConfirmEvent",nullptr);
	UIManager::Get()->PopForntPanel();
}

void BuyCheckPanel::OnClickNo()
{
	UIManager::Get()->PopForntPanel();
}
