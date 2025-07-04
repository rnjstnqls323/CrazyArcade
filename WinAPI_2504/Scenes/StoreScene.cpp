#include "Framework.h"
#include "StoreScene.h"

StoreScene::StoreScene()
{
	player = new Player;
	map = new TileMap("Store.map",Vector2{250,795},Vector2{800,500});
}

StoreScene::~StoreScene()
{
	delete player;
	delete map;
}

void StoreScene::Update()
{
	SpawnBubble();
	CheckCollision();
	player->Update();
	UIManager::Get()->Update(player);
	BubbleManager::Get()->Update();
}

void StoreScene::Render()
{
	map->Render();
	UIManager::Get()->Render();
	BubbleManager::Get()->Render();
	player->Render();


}

void StoreScene::Start()
{
	UIManager::Get()->AddShowPanel(PanelType::StorePanel);
	player->Reset();
	player->SetLocalPosition({ 1000,400 });
	player->UpdateWorld();
	map->Load();
}

void StoreScene::End()
{
	UIManager::Get()->Reset();
}

void StoreScene::SpawnBubble()
{
	if (!Input::Get()->IsKeyDown(VK_SPACE)) return;
	isSpawn = BubbleManager::Get()->SpawnBubble(map->GetTilePos(playerIndex), playerIndex, map);
	if (!isSpawn)
		return;
	map->ChangeTileTypeToBubble(playerIndex);
}

void StoreScene::CheckCollision()
{
	playerIndex = map->CheckCollision(player);

}
