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
		int type = reader->Int(); // 노드인지 몬스터 스폰위치인지 봐주는거
		int tileTag = reader->Int();

		tile->SetTileTag(tileTag);

		SettingTile(tile, filePath);

		

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

void TileMap::SettingTile(Tile* tile, const wstring& filePath)
{
	if (filePath.find(L"Monster") != wstring::npos)
	{
		tile->SetTileType(MonsterSpawnTile);
		return;
	}
	else if (filePath.find(L"None") != wstring::npos)
	{
		tile->SetTileType(BlockTile);
		return;
	}
	else if (filePath.find(L"End") != wstring::npos)
	{
		tile->SetTileType(EndNodeTile);
		return;
	}
	else if (filePath.find(L"Pass") != wstring::npos)
	{
		tile->SetTileType(PassTile);
		return;
	}

	unordered_map<wstring, BlockCategory> fileCategoryMap = {
	{L"Block1",  BlockCategory::Block1},
	{L"Block2",  BlockCategory::Block2},
	{L"Flower1", BlockCategory::Flower1},
	{L"Flower2", BlockCategory::Flower2},
	{L"Shell1",  BlockCategory::Shell1},
	{L"Shell2",  BlockCategory::Shell2}
	};

	for (const auto& map : fileCategoryMap)
	{
		if (filePath.find(map.first) != wstring::npos)
		{
			tile->SetTileType(CrushTile);
			BlockFactory::Get()->AddBlock(map.second, tile->GetLocalPosition());
			return;
		}
	}
	
}
