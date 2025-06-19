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

	for(int y=0;y<ROW;y++)
		for (int x = 0;x < COL;x++)
		{
			tiles[y][x]->RectCollider::Render();
		}
		
}

vector<Tile*> TileMap::GetAroundTile(Index2 index)
{
	vector<Tile*> aroundTile;
	
	if (index.y - 1 >= 0)
		aroundTile.push_back(tiles[index.y - 1][index.x]);
	if (index.y + 1 < ROW)				 
		aroundTile.push_back(tiles[index.y + 1][index.x]);
	if (index.x - 1 >= 0)				 
		aroundTile.push_back(tiles[index.y][index.x - 1]);
	if (index.x < COL)					 
		aroundTile.push_back(tiles[index.y][index.x + 1]);


	return aroundTile;
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

	for (int y = 0;y < ROW;y++)
		for (int x = 0;x < COL;x++)
		{
			filePath = reader->WString();
			int type = reader->Int(); // 노드인지 몬스터 스폰위치인지 봐주는거
			int tileTag = reader->Int();

			tiles[y][x]->SetTileTag(tileTag);

			SettingTile(tiles[y][x], filePath);
		}

	BlockFactory::Get()->CreateInstanceBuffer();
}

void TileMap::CreateTiles()
{
	tiles.resize(ROW);
	for (int y = 0;y < ROW;y++)
		tiles[y].resize(COL);

	tileStartPos = Vector2(TILE_SIZE.x * 0.5f + 100, SCREEN_HEIGHT - TILE_SIZE.y * 0.5f - 30);

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			Tile* tile = new Tile();
			Vector2 pos = tileStartPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->UpdateWorld();
			tiles[y][x] = tile;
		}
	}
}

void TileMap::DeleteTiles()
{
	for(int y=0;y<ROW;y++)
		for (int x = 0;x < COL;x++)
		{
			delete tiles[y][x];
		}
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
