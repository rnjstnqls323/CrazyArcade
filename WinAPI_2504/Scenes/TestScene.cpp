#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	BlockFactory::Get();
	BubbleManager::Get();
	map = new TileMap("Resources/TextData/TestStage1.map");

	player = new Character();
	player->SetLocalPosition(700, 500);
}

TestScene::~TestScene()
{
	BlockFactory::Delete();
	BubbleManager::Delete();
	delete map;
	delete player;
}

void TestScene::Update()
{
	SpawnBubble();

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
}

void TestScene::CheckCollision() //이거 씬에서 계속 확인해주자
{
	Vector2 overlap;
	
	Vector2 tileStartPos = map->GetStartPos();
	Vector2 playerPos = player->GetLocalPosition();
	float halfTileSize = TILE_SIZE.x * 0.5f;
	int x = (int)(playerPos.x - tileStartPos.x) / TILE_SIZE.x + 0.5f;
	int y = (int)(tileStartPos.y- playerPos.y) / TILE_SIZE.y + 0.5f;

	playerIndex = { y,x };
	vector<Tile*> aroundTiles = map->GetAroundTile(playerIndex);

	for (Tile* tile : aroundTiles)
	{
		if (tile->GetTileType() != BlockTile && tile->GetTileType() != CrushTile 
			&& tile->GetTileType() != BubbleTile)
			continue;

		if (tile->IsRectCollision(player, &overlap))
			PushPlayer(overlap, *tile);
	}
}

void TestScene::PushPlayer(const Vector2& overlap, Tile& tile)
{
	Vector2 pos = player->GetLocalPosition();
	Vector2 tilePos = tile.GetLocalPosition();

	float diffX = pos.x - tilePos.x;
	float diffY = pos.y - tilePos.y;

	if (overlap.x < overlap.y)
	{
		if (diffX > 0)
			pos.x += overlap.x;
		else
			pos.x -= overlap.x;
	}
	else
	{
		if (diffY > 0)
			pos.y += overlap.y;
		else
			pos.y -= overlap.y;
	}

	player->SetLocalPosition(pos);
	player->UpdateWorld();
}

void TestScene::SpawnBubble()
{
	if (!Input::Get()->IsKeyDown(VK_SPACE) || map->GetTileType(playerIndex) == BubbleTile) 
		return;
	
	isSpawn = BubbleManager::Get()->SpawnBubble(map->GetTilePos(playerIndex));
	if (!isSpawn)
		return;
	map->ChangeTileType(BubbleTile, playerIndex);
}

