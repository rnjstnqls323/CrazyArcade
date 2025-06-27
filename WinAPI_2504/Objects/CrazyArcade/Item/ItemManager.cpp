#include "Framework.h"

ItemManager::ItemManager()
{
	maxItemCount = ITEM_POOL_SIZE * (int)ItemType::EndItem;
	for (int i = 0;i < ITEM_POOL_SIZE * (int)ItemType::EndItem; i++)
	{
		ItemType type = (ItemType)(i % (int)ItemType::EndItem);
		switch (type)
		{
		case ItemType::BubbleItem:
			CreateItem<BubbleItem>();
			break;
		case ItemType::WaterJetItem:
			CreateItem<WaterJetItem>();
			break;
		case ItemType::SuperWaterJetItem:
			CreateItem<SuperWaterJetItem>();
			break;
		case ItemType::SkateItem:
			CreateItem<SkateItem>();
			break;
		case ItemType::NeedleItem:
			CreateItem<NeedleItem>();
			break;
		}
	}

}

ItemManager::~ItemManager()
{
	for (Item* item : items)
	{
		delete item;
	}
	items.clear();
}

void ItemManager::Update(Player* player)
{
	for (Item* item : items)
	{
		if (!item->IsActive()) continue;
		item->CollisionPlayer(player);
		item->Update();
	}
}

void ItemManager::Render()
{
	for (Item* item : items)
	{
		if (!item->IsActive()) continue;
		item->Render();
	}
}

void ItemManager::Spawn(Vector2 pos)
{
	if (itemCount == maxItemCount) itemCount = 0;
	items[itemCount++]->SpawnItem(pos);
}
