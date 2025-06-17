#pragma once

class TileMap
{
public:
	TileMap(string filePath);
	~TileMap();

	void Update();
	void Render();
	
private:
	void Load();

	void CreateTiles();
	void DeleteTiles();

private:

	string loadFilePath;
	Quad* backGround;
	vector<Tile*> tiles;

};