#pragma once

enum TileType
{
	NoneTile, BlockTile, CrushTile //��ǳ�� �浹�� �����Ϸ��� �ٱ��� �´µ�?
};
class Tile : public RectCollider
{
public:
	Tile();
	~Tile();

	virtual void Update() {};
	virtual void Render() {};
	
	void SetTileType(TileType type) { this->type = type; }

protected:
	TileType type = NoneTile;
};