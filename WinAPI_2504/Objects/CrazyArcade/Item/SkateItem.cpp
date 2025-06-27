#include "Framework.h"

SkateItem::SkateItem()
{
	path += "Skate/";

	LoadAnimation();
}

SkateItem::~SkateItem()
{
}

void SkateItem::PlayerGetItem(Player* player)
{
	player->AddSpeed();
}
