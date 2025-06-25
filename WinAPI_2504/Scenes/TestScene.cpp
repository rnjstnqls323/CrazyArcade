#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	BlockFactory::Get();
	BubbleManager::Get();
	MonsterManager::Get();

	map = new TileMap("Resources/TextData/TestStage1.map");
	MonsterManager::Get()->AddNode(map, map->GetMonsterPos());

	astar = new AStar(map); // 거북왕전용으로쓸거임

	player = new Player();
	player->SetLocalPosition(700, 500);

	MonsterManager::Get()->MonsterSpawn();
}

TestScene::~TestScene()
{
	BlockFactory::Delete();
	BubbleManager::Delete();

	delete map;
	delete player;
	delete astar;
}

void TestScene::Update()
{
	SpawnBubble();

	MonsterManager::Get()->Update();
	CheckCollision();
	player->Update();

	BubbleManager::Get()->Update();

}

void TestScene::Render()
{
	map->Render();
	BlockFactory::Get()->Render();


	BubbleManager::Get()->Render();
	player->Render();
	MonsterManager::Get()->Render();
}

void TestScene::CheckCollision() //이거 씬에서 계속 확인해주자
{
	MonsterManager::Get()->MonsterCollisionPlayer(player);
	playerIndex = map->CheckCollision(player);

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

