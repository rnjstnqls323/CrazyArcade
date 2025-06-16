#pragma once

class MapEditScene :public Scene
{
public:
	MapEditScene();
	~MapEditScene();



	// Scene을(를) 통해 상속됨
	void Update() override;

	void Render() override;
	void GUIRender() override;

private:
	void EditBgTiles();

	void RenderSampleButtons();
	void CreateEditTiles();
	void DeleteEditTiles();

	void LoadTextures();
	void Save(string file);
	void Load(string file);

	void SaveDialog();
	void LoadDialog();

	void MoveTiles();

private:
	Quad* quad;
	vector<Tile*> tiles;
};