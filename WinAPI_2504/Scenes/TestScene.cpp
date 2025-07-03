#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{

	map = new TileMap("TestStage1.map");
	MonsterManager::Get()->AddMonsterPos(map, map->GetMonsterPos());

	player = new Player();
	Vector2 pos = map->GetTilePos(Index2(3,2));
	player->SetLocalPosition(pos);

	MonsterManager::Get()->MonsterSpawn();
	MonsterManager::Get()->SpawnTuttleKing();

}

TestScene::~TestScene()
{

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

	ItemManager::Get()->Update(player,map);
	UIManager::Get()->Update(player);

}

void TestScene::Render()
{
	map->Render();
	BlockFactory::Get()->Render();


	BubbleManager::Get()->Render();

	//MonsterManager::Get()->Render();

	player->Render();
	ItemManager::Get()->Render();
	UIManager::Get()->Render();
}

void TestScene::GUIRender()
{
	playerIndex = map->GetTileIndex(player);


	ImGui::Text("Tile Index: (%f, %f)", playerIndex.x,playerIndex.y);
	ImGui::Text("TileType: %d", (int)map->GetTileType(playerIndex)); 
	ImGui::Text("PreTileType: %d", (int)map->GetPreTileType(playerIndex)); 

}

void TestScene::Start()
{
	player->Reset();
	UIManager::Get()->AddShowPanel(PanelType::PlayPanel);
}

void TestScene::End()
{
	UIManager::Get()->Reset();
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

