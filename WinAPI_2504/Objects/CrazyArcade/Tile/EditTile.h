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
	void SetEditTag(int num) { tag = num; }

	EditTileType GetEditTileType() { return editType; }
	int GetEditTag() { return tag; }

private:
	int tag = -1;

	EditTileType editType = EditTileType::NormalTile;
	Quad* image;

};