#pragma once

class TileMap
{
public:
	TileMap(string filePath);
	~TileMap();

	void Update();
	void Render();

	const vector<Tile*>& GetTiles() { return tiles; }
	
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