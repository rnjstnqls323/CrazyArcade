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
	void Update(TileMap* map);

	bool SpawnBubble(Vector2 pos,Index2 index);

private:
	vector<Bubble*>  bubbles;
	vector<Index2> bubbleIndex;
		//버블마다 타이머설정해둬야겠는디  
};