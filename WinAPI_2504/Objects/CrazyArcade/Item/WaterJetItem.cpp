#include "Framework.h"

WaterJetItem::WaterJetItem()
{
	path += "WaterJet/";
	LoadAnimation();
}

WaterJetItem::~WaterJetItem()
{
}

void WaterJetItem::PlayerGetItem(Player* player)
{
	BubbleManager::Get()->AddJetLength();
}
