#pragma once

enum TileType
{
	PassTile, BlockTile, CrushTile, BubbleTile, WaterTile , MonsterSpawnTile, EndNodeTile 
	//��ǳ�� �浹�� �����Ϸ��� �ٱ��� �´µ�?  End��monster �� ���� �̰� �ʹ� �������.
};
class Tile : public RectCollider
{
public:
	Tile();
	~Tile();

	virtual void Update() {};
	virtual void Render() {};
	
	void SetTileType(TileType type) { this->type = type; }
	TileType GetTileType() { return type; }

	int GetTileTag() { return tag; }
	void SetTileTag(int num) { tag = num; }

protected:
	int tag = -1;

	TileType type = PassTile;
};