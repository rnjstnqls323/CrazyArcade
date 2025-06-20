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

	vector<Tile*> GetAroundTile(Index2 index);

	void ChangeTileType(TileType type, Index2 index)
	{
		tiles[index.y][index.x]->SetTileType(type);
	}
	void ChangeTileTypeToBubble(Index2 index);
	
private:
	void Load();

	void CreateTiles();
	void DeleteTiles();

	void SettingTile(Tile* tile, const wstring& filePath);
private:
	string loadFilePath;
	Quad* backGround;
	vector<vector<Tile*>> tiles;
	Vector2 tileStartPos;
};