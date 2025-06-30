#include "Framework.h"

PlayPannel::PlayPannel()
{
	CreateBackGround();
	CreateButton();
	SetEventFunc();
	CreatePlayerAndNeedle();
}

PlayPannel::~PlayPannel()
{
	delete player;
}

void PlayPannel::Update()
{
	for (Button* button : buttons)
	{
		button->Update();
	}
}

void PlayPannel::Render()
{
	backGround->Render();
	player->Render();
	for (Button* button : buttons)
	{
		button->Render();
	}
}

void PlayPannel::CreateButton()
{
	Button* button = new Button(L"OutButton",Vector2(1112,120), Vector2(200, 30));
	button->SetParent(this);
	button->UpdateWorld();
	buttons.push_back(button);
}

void PlayPannel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Play/Play_UI.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

void PlayPannel::CreatePlayerAndNeedle()
{
	wstring path = Player::GetWstringCharacter() + L".png";
	player = new Quad(L"Resources/Textures/CrazyArcade_UI/Play/"+ path);
	player->SetLocalScale(1.5, 1.5);
	player->SetLocalPosition(Vector2(1065,715));
	player->SetParent(this);
	player->UpdateWorld();
}

void PlayPannel::SetEventFunc()
{
	buttons[0]->SetOnClick([this]() { OutButton(); }); // 이게 람다방식??
}

void PlayPannel::OutButton()
{
	//SceneManager::Get()->ChangeScene("Edit");  아 여기다가 UIManager로 띄우면되겠다! 굿!
}
