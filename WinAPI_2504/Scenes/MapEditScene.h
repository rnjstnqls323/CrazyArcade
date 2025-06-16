#pragma once

class MapEditScene :public Scene
{
public:
	MapEditScene();
	~MapEditScene();



	// Scene��(��) ���� ��ӵ�
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