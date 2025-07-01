#include "Framework.h"

LobyPanel::LobyPanel()
{
	CreateButtons();
	CreateBackGround();
	SetEventFunc();
	CreateCharacterButton();

	playerBG = new PlayerBackGround(Vector2(280, 660));
	playerBG->SetParent(this);
}

LobyPanel::~LobyPanel()
{
	delete playerBG;
}

void LobyPanel::Update(Player* player)
{
	Panel::Update();
	for (auto& button : characterButton)
	{
		button.second->Update();
	}
}

void LobyPanel::Render()
{
	Panel::Render();
	playerBG->Render();
	for (auto& button : characterButton)
	{
		button.second->Render();
	}
}

void LobyPanel::CreateButtons()
{
	CreateButton(L"Start", Vector2(1000, 190), Vector2(280, 70)); 
	CreateButton(L"ItemShopButton", Vector2(1090, 480), Vector2(140, 40));
	CreateButton(L"InventoryButton", Vector2(910, 480), Vector2(140, 40));
	CreateButton(L"ExitButton", Vector2(240, 110), Vector2(40, 30));

}

void LobyPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Loby/Loby.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void LobyPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() {OnClickStartButton();});
	buttons[1]->SetOnClick([this]() {OnClickItemShopButton();});
	buttons[2]->SetOnClick([this]() {OnClickInventoryButton();});
	buttons[3]->SetOnClick([this]() {OnClickExitButton();});
}

void LobyPanel::CreateCharacterButton()
{
	Vector2 startPos = { 500,500 };
	Vector2 AddPos = { 70,50 };

	for (int i = 0;i < (int)CharacterName::EndCharacter;i++)
	{
		wstring name = Player::GetWstringCharacter((CharacterName)i);
		characterButton[(CharacterName)i] = new Button(name, Vector2(startPos.x+ (i + 1) * AddPos.x, startPos.y ), Vector2(50, 50));
		characterButton[(CharacterName)i]->SetParent(this);
		characterButton[(CharacterName)i]->UpdateWorld();
	}
}

void LobyPanel::OnClickStartButton()
{
}

void LobyPanel::OnClickExitButton()
{
	UIManager::Get()->AddShowPanel(PanelType::ExitPanel);
}

void LobyPanel::OnClickItemShopButton()
{
}

void LobyPanel::OnClickInventoryButton()
{
}

void LobyPanel::OnClickCharacterButton(CharacterName name)
{
}
