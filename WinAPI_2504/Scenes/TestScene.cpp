#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	BlockFactory::Get();
	BubbleManager::Get();
	MonsterManager::Get();
	ItemManager::Get();

	map = new TileMap("Resources/TextData/TestStage1.map");
	MonsterManager::Get()->AddMonsterPos(map, map->GetMonsterPos());

	player = new Player();
	player->SetLocalPosition(700, 500);

	MonsterManager::Get()->MonsterSpawn();
	MonsterManager::Get()->SpawnTuttleKing();


}

TestScene::~TestScene()
{
	BlockFactory::Delete();
	BubbleManager::Delete();
	ItemManager::Delete();

	delete map;
	delete player;

}

void TestScene::Update()
{
	SpawnBubble();

	//MonsterManager::Get()->Update(player);
	CheckCollision();
	player->Update();

	BubbleManager::Get()->Update();

	ItemManager::Get()->Update(player);
}

void TestScene::Render()
{
	map->Render();
	BlockFactory::Get()->Render();


	BubbleManager::Get()->Render();

	//MonsterManager::Get()->Render();

	player->Render();
	ItemManager::Get()->Render();
}

void TestScene::CheckCollision() //이거 씬에서 계속 확인해주자
{
	//MonsterManager::Get()->MonsterCollisionPlayer(player); // 매니저업데이트로빼자
	playerIndex = map->CheckCollision(player);
	if (player->IsDieOrTrap()) return;
	if (map->GetTileType(playerIndex) == WaterTile && !player->GetIsTrap())
	{
		player->Trap();
	}
}

void TestScene::SpawnBubble()
{
 	if (!Input::Get()->IsKeyDown(VK_SPACE) 
		|| map->GetTileType(playerIndex) == BubbleTile || map->GetTileType(playerIndex) == WaterTile)
		return;
	
	isSpawn = BubbleManager::Get()->SpawnBubble(map->GetTilePos(playerIndex),playerIndex,map);
	if (!isSpawn)
		return;
	map->ChangeTileTypeToBubble(playerIndex); 
}

