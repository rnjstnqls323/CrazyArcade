#include "Framework.h"


TileMap::TileMap(string filePath)
{
	this->loadFilePath = filePath;
	Load();
}

TileMap::~TileMap()
{
	delete backGround;
	DeleteTiles();
}

void TileMap::Update()
{
}

void TileMap::Render()
{
	backGround->Render();

	for (Tile* tile : tiles)
		tile->RectCollider::Render();
}

void TileMap::Load()
{
	BinaryReader* reader = new BinaryReader(loadFilePath);
	if (reader->IsFailed())
	{
		delete reader;
		return;
	}
	UINT tag = reader->UInt(); // 이걸 받을필요가있나? 아근데 무조건 받긴해야되네 안써도 ㅇㅇ
	UINT tileCount = reader->UInt();
	wstring filePath = reader->WString();

	backGround = new Quad(filePath);
	backGround->SetLocalPosition({ 600,480 });
	backGround->UpdateWorld();

	CreateTiles();

	for (Tile* tile : tiles)
	{
		filePath = reader->WString();
		int type = reader->Int();
		int tileTag = reader->Int();
		

	}
}

void TileMap::CreateTiles()
{

	Vector2 startPos = Vector2(TILE_SIZE.x * 0.5f + 100, SCREEN_HEIGHT - TILE_SIZE.y * 0.5f - 30);

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			Tile* tile = new Tile();
			Vector2 pos = startPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->UpdateWorld();
			tiles.push_back(tile);
		}
	}
}

void TileMap::DeleteTiles()
{
	for (Tile* tile : tiles)
		delete tile;
	tiles.clear();
}
