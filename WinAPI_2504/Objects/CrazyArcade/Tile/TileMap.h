#pragma once

class TileMap
{
public:
	TileMap(wstring filePath);
	~TileMap();

	void Update();
	void Render();

	void Save();
	void Load();

	void CreateTile();
	void ClearTile();

	void SetBackGroundImage(wstring filePath); //이부분은 .map받아오면 없어질 예정임
private:
	Quad* backGroundImage;
	vector<Tile*> tiles;

};