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

	//void Update(); // FSM할때, 상태값따라서 충돌등 다르게 구현하자

	void SetTileType(TileType type) { this->type = type; }

private:
	Quad* quad;
	TileType type = NoneTile;
};