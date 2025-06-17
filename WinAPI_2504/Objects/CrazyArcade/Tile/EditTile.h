#pragma once

enum class EditTileType
{
	MonsterTilePos, NormalTile, EndNodeTilePos
};

class EditTile : public Tile
{

public:
	EditTile();
	~EditTile();

	void Update() override;
	void Render() override;

	Quad* GetImage() { return image; }

	void SetEditTileType(EditTileType editType) { this->editType = editType; }

	EditTileType GetEditTileType() { return editType; }


private:


	EditTileType editType = EditTileType::NormalTile;
	Quad* image;

};