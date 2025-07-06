#include "Framework.h"

PlayPanel::PlayPanel()
{
	type = PanelType::PlayPanel;
	CreateBackGround();
	CreateButtons();
	CreatePlayerAndNeedle();
	CreateTimer();

	SetEventFunc();
}

PlayPanel::~PlayPanel()
{
	delete player;
	for (Quad* quad : showTime)
	{
		delete quad;
	}
	showTime.clear();
}

void PlayPanel::Update(Player* player)
{
	Panel::Update(player);
	isNeedle = player->IsHaveNeedle();
	ChangeTime();
}

void PlayPanel::Render()
{
	Panel::Render();
	player->Render();
	if(isNeedle)
		needle->Render(); 
	for (Quad* quad : showTime)
	{
		quad->Render();
	}
}

void PlayPanel::CreateButtons()
{
	CreateButton(L"OutButton", Vector2(1112, 120), Vector2(180, 40));
}

void PlayPanel::CreateBackGround()
{
	backGround = new Quad(path+L"backGround.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void PlayPanel::CreatePlayerAndNeedle()
{
	player = new PlayerViewSmall();

	needle = new Quad(path+L"Needle.png");
	needle->SetLocalPosition(Vector2(1080, 205));
	needle->SetParent(this);
	needle->UpdateWorld();
}

void PlayPanel::CreateTimer()
{
	showTime.resize(4);
	Vector2 startPos = { 1112,762 };
	float addX = 20;
	int count = 0;
	for (Quad*& quad : showTime)
	{
		quad = new Quad(path + L"0.png");
		quad->SetParent(this);
		quad->SetLocalScale(0.7, 0.8);
		quad->SetLocalPosition(startPos.x + addX * count++, startPos.y);
		quad->UpdateWorld();
	}
}

void PlayPanel::ChangeTime()
{
	timer+=DELTA;
	if (timer < 1.0f || leftTime <=0.0f) return;
	timer -= 1.0f;
	leftTime -= 1.0f;
	if (leftTime <= 0.0f)
	{
		UIManager::Get()->AddShowPanel(PanelType::LosePanel);
	}
	int minutes = (int)leftTime / 60;
	int seconds = (int)leftTime % 60;

	int m1 = minutes / 10;
	int m2 = minutes % 10;
	int s1 = seconds / 10;
	int s2 = seconds % 10;

	showTime[0]->GetMaterial()->SetBaseMap(path + to_wstring(m1) + L".png");
	showTime[1]->GetMaterial()->SetBaseMap(path + to_wstring(m2) + L".png");
	showTime[2]->GetMaterial()->SetBaseMap(path + to_wstring(s1) + L".png");
	showTime[3]->GetMaterial()->SetBaseMap(path + to_wstring(s2) + L".png");
}

void PlayPanel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() { OutButton(); }); // 이게 람다방식??
}

void PlayPanel::OutButton()
{
	UIManager::Get()->AddShowPanel(PanelType::GoBackPanel);
}

void PlayPanel::Reset()
{
	leftTime = 180.0f;
	timer = 1.0f;
	isNeedle = false;
}

