#include "Framework.h"

LobyPanel::LobyPanel()
{
	CreateButtons();
	CreateBackGround();
	CreateCharacterButton();
	SetEventFunc();

	playerBG = new PlayerBackGround(Vector2(280, 660));
	playerBG->SetParent(this);
	CreatePlayerAndSelectPanel();
}

LobyPanel::~LobyPanel()
{
	delete playerBG;
	delete player;
	delete selectPlayerPanel;
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
	player->Render();
	selectPlayerPanel->Render();
}

void LobyPanel::CreateButtons()
{
	CreateButton(L"Start", Vector2(1000, 190), Vector2(280, 70)); 
	CreateButton(L"ItemShopButton", Vector2(1090, 480), Vector2(140, 40));
	CreateButton(L"InventoryButton", Vector2(910, 480), Vector2(140, 40));
	CreateButton(L"ExitButton", Vector2(1175, 110), Vector2(40, 30));

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

	for (int i = 0; i < (int)CharacterName::EndCharacter; i++)
	{
		CharacterName name = (CharacterName)i;
		characterButton[name]->SetOnClick([this, name]() {OnClickCharacterButton(name);	});
	}
}

void LobyPanel::CreateCharacterButton()
{
	Vector2 startPos = { 775,700 };
	float AddPos = 75;

	for (int i = 0;i < (int)CharacterName::EndCharacter;i++)
	{
		wstring name = Player::GetWstringCharacter((CharacterName)i);
		characterButton[(CharacterName)i] = new Button(name, Vector2(startPos.x+ (i + 1) * AddPos, startPos.y ), Vector2(60, 40));
		characterButton[(CharacterName)i]->SetParent(this);
		characterButton[(CharacterName)i]->UpdateWorld();
	}
}

void LobyPanel::CreatePlayerAndSelectPanel()
{
	wstring playerName = Player::GetWstringCharacter(Player::GetCharacter());
	player = new Quad(path+ playerName +L".png");
	player->SetLocalPosition(Vector2(280,650));
	player->SetParent(this);
	player->UpdateWorld();

	selectPlayerPanel = new Quad(path + playerName + L"Panel.png");
	selectPlayerPanel->SetLocalPosition(Vector2(1000,800));
	selectPlayerPanel->SetParent(this);
	selectPlayerPanel->UpdateWorld();
}


void LobyPanel::OnClickStartButton()
{
	SCENE->ChangeScene("Game");
}

void LobyPanel::OnClickExitButton()
{
	UIManager::Get()->AddShowPanel(PanelType::ExitPanel);
}

void LobyPanel::OnClickItemShopButton()
{
	SCENE->ChangeScene("Store");
}

void LobyPanel::OnClickInventoryButton()
{
	UIManager::Get()->AddShowPanel(PanelType::InventoryPanel);
}

void LobyPanel::OnClickCharacterButton(CharacterName name)
{
	Player::SetCharacter(name);
	wstring playerName = Player::GetWstringCharacter(Player::GetCharacter());
	player->GetMaterial()->SetBaseMap(path + playerName + L".png");
	selectPlayerPanel->GetMaterial()->SetBaseMap(path + playerName + L"Panel.png");
}
