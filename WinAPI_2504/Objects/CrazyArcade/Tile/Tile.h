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

	//void Update(); // FSM�Ҷ�, ���°����� �浹�� �ٸ��� ��������

	void SetTileType(TileType type) { this->type = type; }

private:
	Quad* quad;
	TileType type = NoneTile;
};