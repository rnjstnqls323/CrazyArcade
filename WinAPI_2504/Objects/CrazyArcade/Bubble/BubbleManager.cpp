#include "Framework.h"

BubbleManager::BubbleManager()
{
	bubbles.resize(BUBBLE_POOL_SIZE);
	int num = 0;
	for (Bubble*& bubble : bubbles)
	{
		bubble = new Bubble;
		bubble->SetTag(num++);
	}
}

BubbleManager::~BubbleManager()
{
	for (Bubble* bubble : bubbles)
		delete bubble;
	bubbles.clear();
}

void BubbleManager::Render()
{
	for (Bubble* bubble : bubbles)
	{
		if (!bubble->IsActive())
			continue;
		bubble->Render();
	}
}

void BubbleManager::Update()
{

	for (Bubble* bubble : bubbles)
	{
		if (!bubble->IsActive())
			continue;
		bubble->Update();
		if (bubble->GetStatus() == Exploding)
		{
			map->SetTileType(WaterTile, bubble->GetBubbleIndex());
		}
		else if (bubble->GetStatus() == Dead)
		{
 			bubble->SetActive(false);
			map->SetTileType(PassTile, bubble->GetBubbleIndex());
		}
	}
}

bool BubbleManager::SpawnBubble(Vector2 pos, Index2 index,TileMap* map)
{
		this->map = map;
	for (Bubble* bubble : bubbles)
	{
		if (bubble->IsActive())
			continue;
		bubble->Spawn(pos,index,map);

		return true;
	}
	return false;
}

void BubbleManager::BombBubble(Index2 index)
{
	
	for (Bubble* bubble : bubbles)
	{
		if (!bubble->IsActive())
			continue;
		if (bubble->GetBubbleIndex() != index)
			continue;
		map->SetTileType(PassTile, index);
		bubble->SetBombTime();
	}
}

