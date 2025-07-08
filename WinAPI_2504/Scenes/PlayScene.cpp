#include "Framework.h"
#include "PlayScene.h"

bool PlayScene::isSetEvent = false;
PlayScene::PlayScene()
{
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
	if (Input::Get()->IsKeyDown(VK_F1))
		UIManager::Get()->AddShowPanel(PanelType::WinPanel);
	StopAudio();
	UIManager::Get()->Update(player);

	if (isEnd) return; // 만약 끝났으면 아래 업데이트하지말고 리턴
	MonsterManager::Get()->Update(player);
	player->Update();
	CheckCollision();
	if (!isStart) return; // 시작 아직안했으면 버블 못쏘게

	SpawnBubble();

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
	Audio::Get()->Play(audioKey);
	BubbleManager::Get()->Reset();
	player->Reset();
	MonsterManager::Get()->Reset();

	UIManager::Get()->AddShowPanel(PanelType::PlayPanel);
	UIManager::Get()->AddShowPanel(PanelType::PlayStartPanel);
	Audio::Get()->Play("ef_GameStart");
	map->Load();
	MonsterManager::Get()->AddMonsterPos(map, map->GetMonsterPos());
	Vector2 pos = map->GetTilePos(Index2(3, 2));

	player->SetLocalPosition(pos);
	isEnd = false;
	isSpawn = false;
	isStart = false;
	isStop = false;

	MonsterManager::Get()->MonsterSpawn();

	eventKey = EventManager::Get()->AddEvent("ChangeStage", [this](void* param) {ChangeStage();});

}

void PlayScene::End()
{
	Audio::Get()->Stop(audioKey);
	UIManager::Get()->Reset();
	ItemManager::Get()->Reset();

	EventManager::Get()->RemoveEvent("ChangeStage", eventKey);
}

void PlayScene::StopAudio()
{
	if (UIManager::Get()->GetFrontPanelType() != PanelType::PlayPanel)
	{
		Audio::Get()->Stop(audioKey);
		isStop = true;
	}
	else if (isStop)
	{
		isStop = false;
		Audio::Get()->Play(audioKey);
	}
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

