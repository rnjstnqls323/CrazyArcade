#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	BlockFactory::Get();
	map = new TileMap("Resources/TextData/TestStage1.map");

	player = new Character();
	player->SetLocalPosition(500, 500);
}

TestScene::~TestScene()
{
	BlockFactory::Delete();
	delete map;
	delete player;
}

void TestScene::Update()
{
	CheckCollision();
	player->Update();

}

void TestScene::Render()
{
	map->Render();
	BlockFactory::Get()->Render();
	player->Render();
}

void TestScene::CheckCollision() //이거 씬에서 계속 확인해주자
{
	vector<Tile*> tiles = map->GetTiles();
	for (Tile* tile : tiles)
	{
		if (tile->GetTileType() != BlockTile && tile->GetTileType() != CrushTile)
			continue;

		Vector2 overlap;
		if (!player->IsRectCollision(tile, &overlap))
			continue;

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

