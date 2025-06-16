#pragma once

class EditTile : public Tile
{
public:
	EditTile();
	~EditTile();

	void Update() override;
	void Render() override;

	Quad* GetImage() { return image; }

private:
	Quad* image;

};