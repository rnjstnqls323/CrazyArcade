#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	BlockFactory::Get();
	map = new TileMap("Resources/TextData/TestStage1.map");

	player = new Character();
	player->SetLocalPosition(700, 500);
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
	Vector2 overlap;

	vector<Tile*> tiles = map->GetTiles();
	int count = 0;

	for (Tile* tile : tiles)
	{	
		Vector2 tilePos = tile->GetLocalPosition();
		Vector2 playerPos = player->GetLocalPosition();
		float halfSize = TILE_SIZE.x * 0.5f;
		if (tilePos.x - halfSize<playerPos.x && tilePos.x + halfSize>playerPos.x 
			&& tilePos.y - halfSize<playerPos.y && tilePos.y + halfSize>playerPos.y)
			break;
		count++;
	}

	int offset[] = { -1,1,-COL,COL };
	for (int off : offset)
	{
		int index = count + off;
		if (index <= 0 || index > (int)tiles.size())
			continue;
		if (tiles[index]->GetTileType() != BlockTile && tiles[index]->GetTileType() != CrushTile)
			continue;

		if (tiles[index]->IsRectCollision(player, &overlap))
			PushPlayer(overlap, *tiles[index]);
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

