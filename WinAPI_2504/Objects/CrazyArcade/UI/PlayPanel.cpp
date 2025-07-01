#include "Framework.h"

PlayPanel::PlayPanel()
{
	CreateBackGround();
	CreateButtons();
	SetEventFunc();
	CreatePlayerAndNeedle();
}

PlayPanel::~PlayPanel()
{
	delete player;
}

void PlayPanel::Update(Player* player)
{
	Panel::Update(player);
	isNeedle = player->IsHaveNeedle();
}

void PlayPanel::Render()
{
	Panel::Render();
	player->Render();
	if(isNeedle)
		needle->Render(); 
}

void PlayPanel::CreateButtons()
{
	CreateButton(L"OutButton", Vector2(1112, 120), Vector2(180, 40));
}

void PlayPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Play/Play_UI.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void PlayPanel::CreatePlayerAndNeedle()
{
	player = new PlayerViewSmall();

	needle = new Quad(L"Resources/Textures/CrazyArcade_UI/Play/Needle.png");
	needle->SetLocalPosition(Vector2(1080, 205));
	needle->SetParent(this);
	needle->UpdateWorld();
}

void PlayPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() { OutButton(); }); // 이게 람다방식??
}

void PlayPanel::OutButton()
{
	UIManager::Get()->AddShowPanel(PanelType::ExitPanel);
}

