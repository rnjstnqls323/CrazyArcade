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

	bool SpawnBubble(Vector2 pos);
private:
	vector<Bubble*>  bubbles;
		//������ Ÿ�̸Ӽ����ص־߰ڴµ�  
};