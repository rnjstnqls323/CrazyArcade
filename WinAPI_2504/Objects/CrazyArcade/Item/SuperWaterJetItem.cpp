#include "Framework.h"

SuperWaterJetItem::SuperWaterJetItem()
{
	path += "SuperWaterJet/";
	LoadAnimation();
}

SuperWaterJetItem::~SuperWaterJetItem()
{
}

void SuperWaterJetItem::PlayerGetItem(Player* player)
{
	BubbleManager::Get()->SetJetLengthMax();
}
