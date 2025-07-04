#pragma once

class TileMap
{
public:
	TileMap(string filePath,Vector2 startPos = Vector2(TILE_SIZE.x * 0.5f + 100, SCREEN_HEIGHT - TILE_SIZE.y * 0.5f - 30),Vector2 backGroundPos = Vector2(600,480));
	~TileMap();

	void Render();
	void Load();
	
	Vector2 GetStartPos() { return tileStartPos; }

	Vector2 GetTilePos(Index2 index) { return tiles[index.y][index.x]->GetLocalPosition(); }
	TileType GetTileType(Index2 index) { return tiles[index.y][index.x]->GetTileType(); }
	TileType GetPreTileType(Index2 index) { return tiles[index.y][index.x]->GetPreTileType(); }
	vector<Tile*> GetAroundTile(Index2 index);
	vector<Tile*> GetAroundEightTile(Index2 index);
	int GetTileTag(Index2 index) { return tiles[index.y][index.x]->GetTileTag(); }

	void MakeNodes(vector<Node*>& nodes);

	void SetTileType(TileType type, Index2 index)
	{
		tiles[index.y][index.x]->SetTileType(type);
	}
	void SetTileTag(int num, Index2 index) { tiles[index.y][index.x]->SetTileTag(num); }

	void ChangeTileTypeToBubble(Index2 index);

	bool IsIndexInBound(Index2 index)
	{
		if(index.x < 0 || index.y < 0|| index.x > COL-1 || index.y > ROW-1)
			return false;
		return true;
	}

	void CrushBlock(Index2 index);

	const unordered_map<int, MonsterPos>& GetMonsterPos() { return monsterPos; }

	Index2 CheckCollision(RectCollider* collider);
	Index2 GetTileIndex(RectCollider* collider);
	
private:
	void PushCollider(Vector2 overlap, Tile& tile, RectCollider* collider);


	void CreateTiles();
	void DeleteTiles();

	void SettingTile(Tile* tile, const wstring& filePath);


private:
	bool isCreate = false;
	string loadFilePath;
	Quad* frontUI;
	Quad* backGround;
	vector<vector<Tile*>> tiles;
	Vector2 tileStartPos;
	Vector2 backGroundPos;
	unordered_map<int, MonsterPos> monsterPos;
};