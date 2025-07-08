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

void ItemManager::Update(Player* player, TileMap* map)
{
	for (Item* item : items)
	{
		if (!item->IsActive()) continue;
		item->CollisionPlayer(player);
		WaterDeleteItem(item, map);
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
	int num = rand() % 10;
	if (num > 2) return;
	if (itemCount == maxItemCount) itemCount = 0;
	items[itemCount++]->SpawnItem(pos);
}

void ItemManager::Reset()
{
	for (Item* item : items)
	{
		if (!item->IsActive()) continue;
		item->SetActive(false);
	}
}

void ItemManager::WaterDeleteItem(Item* item,TileMap* map)
{
	Index2 index = map->GetTileIndex(item);
	if (map->GetTileType(index) == WaterTile)
		item->SetActive(false);
}
