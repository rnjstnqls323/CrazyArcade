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

	void SetBackGroundImage(wstring filePath); //�̺κ��� .map�޾ƿ��� ������ ������
private:
	Quad* backGroundImage;
	vector<Tile*> tiles;

};