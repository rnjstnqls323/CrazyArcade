#pragma once

class MapEditScene :public Scene
{
private:
	const int COL_BUTTON_NUM = 4;

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

	void CreateBackGround();

	void LoadTextures();
	void Save(string file);
	void Load(string file);

	void SaveDialog();
	void LoadDialog();

	void ResetTiles();

private: 
	int tag = 0;

	Quad* backGround;

	vector<EditTile*> tiles; 
	

	vector<Texture*> sampleTextures;
	vector<Texture*> sampleBackground;
	
	Texture* selectTexture;

};