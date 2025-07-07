#include "Framework.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	EventManager::Get()->AddEvent("ChangeStage", [this](void* param) {ChangeStage();});
	EventManager::Get()->AddEvent("EndStage", [this](void* param) {SetIsEndTrue();});
	EventManager::Get()->AddEvent("StartStage", [this](void* param) {StartGame();});
}

PlayScene::~PlayScene()
{
	delete map;
	delete player;
}

void PlayScene::Update()
{
	UIManager::Get()->Update(player);
	if (isEnd) return;
	MonsterManager::Get()->Update(player);
	player->Update();
	if (!isStart) return;
	SpawnBubble();
	CheckCollision();

	BubbleManager::Get()->Update();
	ItemManager::Get()->Update(player, map);
}

void PlayScene::Render()
{
	map->Render();
	BlockFactory::Get()->Render();
	BubbleManager::Get()->Render();
	MonsterManager::Get()->Render();
	player->Render();
	ItemManager::Get()->Render();
	UIManager::Get()->Render();
}

void PlayScene::Start()
{
	player->Reset();
	MonsterManager::Get()->Reset();
	UIManager::Get()->AddShowPanel(PanelType::PlayPanel);
	UIManager::Get()->AddShowPanel(PanelType::PlayStartPanel);
	map->Load();
	MonsterManager::Get()->AddMonsterPos(map, map->GetMonsterPos());
	Vector2 pos = map->GetTilePos(Index2(3, 2));
	player->SetLocalPosition(pos);
	isEnd = false;
	isSpawn = false;
	isStart = false;

	MonsterManager::Get()->MonsterSpawn();
}

void PlayScene::End()
{
	UIManager::Get()->Reset();
}

void PlayScene::CheckCollision()
{
	playerIndex = map->CheckCollision(player);
	if (player->IsDieOrTrap()) return;
	if (map->GetTileType(playerIndex) == WaterTile && !player->GetIsTrap())
	{
		player->Trap();
	}
}

void PlayScene::SpawnBubble()
{
	if (!Input::Get()->IsKeyDown(VK_SPACE)
		|| map->GetTileType(playerIndex) == BubbleTile || map->GetTileType(playerIndex) == WaterTile)
		return;

	isSpawn = BubbleManager::Get()->SpawnBubble(map->GetTilePos(playerIndex), playerIndex, map);
	if (!isSpawn)
		return;
	map->ChangeTileTypeToBubble(playerIndex);
}

void PlayScene::ChangeStage()
{
	switch (curStatus)
	{
	case Stage1:
		SCENE->ChangeScene("Stage2");
		break;
	case Stage2:
		SCENE->ChangeScene("BossStage");
		break;
	case Boss:
		SCENE->ChangeScene("Loby");
		break;
	}
}

