#pragma once

class BubbleManager :public Singleton<BubbleManager>
{
	friend class Singleton;

private:
	const int BUBBLE_POOL_SIZE = 20;

private:
	BubbleManager();
	~BubbleManager();

public:
	void Render();
	void Update();

	bool SpawnBubble(Vector2 pos,Index2 index,TileMap* map);
	void BombBubble(Index2 index);

private:
	int tag = 0;
	TileMap* map;

	vector<Bubble*> bubbles;
		//버블마다 타이머설정해둬야겠는디  
};