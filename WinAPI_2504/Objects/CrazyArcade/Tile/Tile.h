#pragma once

enum TileType
{
	PassTile, BlockTile, CrushTile, BubbleTile, WaterTile , MonsterSpawnTile, EndNodeTile 
	//물풍선 충돌등 구현하려면 바깥이 맞는듯?  End랑monster 걍 빼자 이거 너무 길어진다.
};
class Tile : public RectCollider
{
public:
	Tile();
	~Tile();

	virtual void Update() {};
	virtual void Render() {};
	
	void SetTileType(TileType type) 
	{ 
		preType = this->type;
		this->type = type;
	}
	TileType GetTileType() { return type; }
	TileType GetPreTileType() { return preType; }


	int GetTileTag() { return tag; }
	void SetTileTag(int num) { tag = num; }

protected:
	int tag = -1;

	TileType type = PassTile;
	TileType preType = PassTile;
};