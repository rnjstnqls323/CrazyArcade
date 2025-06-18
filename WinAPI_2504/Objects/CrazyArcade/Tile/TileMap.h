#pragma once

class TileMap
{
public:
	TileMap(string filePath);
	~TileMap();

	void Update();
	void Render();

	const vector<Tile*>& GetTiles() { return tiles; }
	Tile* GetTile(int row, int col)
	{
		if (row < 0 || row >= ROW || col < 0 || col >= COL)
			return nullptr;
		return tiles[row * COL + col]; // Áß¿ä!
	}
	
private:
	void Load();

	void CreateTiles();
	void DeleteTiles();

	void SettingTile(Tile* tile, const wstring& filePath);
private:

	string loadFilePath;
	Quad* backGround;
	vector<Tile*> tiles;

};