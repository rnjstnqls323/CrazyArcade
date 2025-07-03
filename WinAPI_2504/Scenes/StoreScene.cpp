#include "Framework.h"
#include "StoreScene.h"

StoreScene::StoreScene()
{
	player = new Player;
	player->SetLocalPosition(CENTER);
	player->UpdateWorld();
}

StoreScene::~StoreScene()
{
	delete player;
}

void StoreScene::Update()
{
	player->Update();
	UIManager::Get()->Update(player);
}

void StoreScene::Render()
{
	UIManager::Get()->Render();
	player->Render();
}

void StoreScene::Start()
{
	UIManager::Get()->AddShowPanel(PanelType::StorePanel);
	player->Reset();
}

void StoreScene::End()
{
	UIManager::Get()->Reset();
}
