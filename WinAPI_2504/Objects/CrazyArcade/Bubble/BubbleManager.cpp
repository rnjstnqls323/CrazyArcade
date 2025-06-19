#include "Framework.h"

BubbleManager::BubbleManager()
{
	bubbles.resize(BUBBLE_POOL_SIZE);
	for (Bubble*& bubble : bubbles)
	{
		bubble = new Bubble;
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
	}
}

bool BubbleManager::SpawnBubble(Vector2 pos)
{
	for (Bubble* bubble : bubbles)
	{
		if (bubble->IsActive())
			continue;
		bubble->Spawn(pos);
		return true;
	}
	return false;
}
