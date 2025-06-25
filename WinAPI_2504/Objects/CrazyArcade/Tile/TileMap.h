#pragma once

class TileMap
{
public:
	TileMap(string filePath);
	~TileMap();

	void Update();
	void Render();

	
	Vector2 GetStartPos() { return tileStartPos; }

	Vector2 GetTilePos(Index2 index) { return tiles[index.y][index.x]->GetLocalPosition(); }
	TileType GetTileType(Index2 index) { return tiles[index.y][index.x]->GetTileType(); }
	TileType GetPreTileType(Index2 index) { return tiles[index.y][index.x]->GetPreTileType(); }
	vector<Tile*> GetAroundTile(Index2 index);

	void MakeNodes(vector<Node*>& nodes);

	void SetTileType(TileType type, Index2 index)
	{
		tiles[index.y][index.x]->SetTileType(type);
	}
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
	void Load();

	void CreateTiles();
	void DeleteTiles();

	void SettingTile(Tile* tile, const wstring& filePath);


private:
	string loadFilePath;
	Quad* backGround;
	vector<vector<Tile*>> tiles;
	Vector2 tileStartPos;
	unordered_map<int, MonsterPos> monsterPos;
};