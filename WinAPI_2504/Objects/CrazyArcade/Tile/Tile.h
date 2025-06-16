#pragma once

enum TileType
{
	NoneTile, BlockTile, CrushTile //물풍선 충돌등 구현하려면 바깥이 맞는듯?
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