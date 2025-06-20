#include "Framework.h"

BubbleManager::BubbleManager()
{
	bubbles.resize(BUBBLE_POOL_SIZE);
	bubbleIndex.resize(BUBBLE_POOL_SIZE);
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

void BubbleManager::Update(TileMap* map)
{
	for (Bubble* bubble : bubbles)
	{
		if (!bubble->IsActive())
			continue;
		bubble->Update();
		if (bubble->GetStatus() == Exploding)
		{
 			map->ChangeTileType(WaterTile, bubbleIndex[bubble->GetTag()]);
		}
		else if (bubble->GetStatus() == Dead)
		{
			bubble->SetActive(false);
			map->ChangeTileType(PassTile, bubbleIndex[bubble->GetTag()]);
		}
	}
}

bool BubbleManager::SpawnBubble(Vector2 pos, Index2 index)
{
	for (Bubble* bubble : bubbles)
	{
		if (bubble->IsActive())
			continue;
		bubble->Spawn(pos);
		bubbleIndex[bubble->GetTag()]=index;
		return true;
	}
	return false;
}

