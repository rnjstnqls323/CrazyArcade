#include "Framework.h"

BubbleItem::BubbleItem()
{
	path += "Bubble/";

	LoadAnimation();
}

BubbleItem::~BubbleItem()
{
}

void BubbleItem::PlayerGetItem(Player* player)
{
	BubbleManager::Get()->AddMaxBubble();
}
