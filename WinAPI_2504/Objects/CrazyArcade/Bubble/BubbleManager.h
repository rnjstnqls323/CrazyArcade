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
		//������ Ÿ�̸Ӽ����ص־߰ڴµ�  
};