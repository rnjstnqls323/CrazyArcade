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

void TileMap::MakeNodes(vector<Node*>& nodes)
{
	for (int y = 0;y < ROW;y++)
		for (int x = 0;x < COL;x++)
		{
			Tile* tile = tiles[y][x];
			Node* node = new Node(tile->GetLocalPosition(), nodes.size());

			if (tile->GetTileType() == BlockTile)
				node->SetState(Node::Obstacle);
			//물풍선 있으면 업데이트로 막아주는것도 계속해야됨

			nodes.push_back(node);
		}
}

void TileMap::ChangeTileTypeToBubble(Index2 index)
{
	tiles[index.y][index.x]->SetTileType(BubbleTile);
}

void TileMap::CrushBlock(Index2 index)
{
	Tile* tile = tiles[index.y][index.x];
	tile->SetTileType(PassTile);
	BlockFactory::Get()->PopBlock(tile->GetCategory(), tile->GetLocalPosition());
}

Index2 TileMap::CheckCollision(RectCollider* collider)
{
	Vector2 overlap;

	Index2 colliderIndex = GetTileIndex(collider);
	vector<Tile*> aroundTiles =GetAroundTile(colliderIndex);

	for (Tile* tile : aroundTiles)
	{
		if (tile->GetTileType() != BlockTile && tile->GetTileType() != CrushTile
			&& tile->GetTileType() != BubbleTile)
			continue;

		if (tile->IsRectCollision(collider, &overlap))
			PushCollider(overlap, *tile, collider);
	}
	return colliderIndex;
}

Index2 TileMap::GetTileIndex(RectCollider* collider)
{

	Vector2 tileStartPos = GetStartPos();
	Vector2 colliderPos = collider->GetLocalPosition();
	float halfTileSize = TILE_SIZE.x * 0.5f;
	int x = (int)(colliderPos.x - tileStartPos.x) / TILE_SIZE.x + 0.5f;
	int y = (int)(tileStartPos.y - colliderPos.y) / TILE_SIZE.y + 0.5f;

	Index2 colliderIndex = { y,x };
	return colliderIndex;
}

void TileMap::PushCollider(Vector2 overlap, Tile& tile, RectCollider* collider)
{
	Vector2 pos = collider->GetLocalPosition();
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

	collider->SetLocalPosition(pos);
	collider->UpdateWorld();
}

void TileMap::Load()
{
	BinaryReader* reader = new BinaryReader(loadFilePath);
	if (reader->IsFailed())
	{
		delete reader;
		return;
	}
	UINT tag = reader->UInt(); 
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
			int type = reader->Int(); // 노드인지 몬스터 스폰위치인지 봐주는거 이걸읽을필요가있나?
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
	if (filePath.find(L"Monster1") != wstring::npos)
	{
		tile->SetTileType(MonsterSpawnTile);
		monsterPos[tile->GetTileTag()].startPos = tile->GetLocalPosition();
		monsterPos[tile->GetTileTag()].type = MonsterType::PinkStar;
		return;
	}
	else if (filePath.find(L"Monster2") != wstring::npos)
	{
		tile->SetTileType(MonsterSpawnTile);
		monsterPos[tile->GetTileTag()].startPos = tile->GetLocalPosition();
		monsterPos[tile->GetTileTag()].type = MonsterType::PurpleStar;
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
		monsterPos[tile->GetTileTag()].endPos = tile->GetLocalPosition();
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
			tile->SetCategory(map.second);
			BlockFactory::Get()->AddBlock(map.second, tile->GetLocalPosition());
			return;
		}
	}
}
