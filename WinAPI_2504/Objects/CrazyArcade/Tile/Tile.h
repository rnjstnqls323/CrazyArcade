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

	BlockCategory GetCategory() { return category; }
	void SetCategory(BlockCategory category) { this->category = category; }

	TileType GetTileType() { return type; }
	TileType GetPreTileType() { return preType; }

	int GetTileTag() { return tag; }
	void SetTileTag(int num) { tag = num; }

	Index2 GetTileIndex() { return index; }
	void SetTileIndex(Index2 index) { this->index = index; }

protected:
	int tag = -1;

	Index2 index;
	BlockCategory category;
	TileType type = PassTile;
	TileType preType = PassTile; //이거 왜 냅뒀더라
};