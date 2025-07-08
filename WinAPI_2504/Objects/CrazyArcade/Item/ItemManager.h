#pragma once

class ItemManager : public Singleton<ItemManager>
{
	friend class Singleton;

private:
	const int ITEM_POOL_SIZE = 5;
private:
	ItemManager();
	~ItemManager();


public:
	void Update(Player* player, TileMap* map);
	void Render();
	void Spawn(Vector2 pos);

	void Reset();
private:
	void WaterDeleteItem(Item* item, TileMap* map);
	template<typename T>
	void CreateItem() 
	{
		T* item = new T;
		item->SetActive(false);
		items.push_back(item);
	}
private:
	int maxItemCount = 0;
	int itemCount = 0;
	vector<Item*> items;
};