#include "Framework.h"

NeedleItem::NeedleItem()
{
	path += "Needle/";
	LoadAnimation();
}

NeedleItem::~NeedleItem()
{
}

void NeedleItem::PlayerGetItem(Player* player)
{
	player->AddNeedle();
}
