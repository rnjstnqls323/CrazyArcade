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

	void SetBubbles(int bubbleCount, int jetCount);

	void SetJetLengthMax();
	void AddJetLength();
	void AddMaxBubble();

	void Reset();
	
	void ChangeBubbleType(BubbleType type) { bubbles[0]->SetBubbleType(type); }
	BubbleType GetBubbleType() { return bubbles[0]->GetBubbleType(); }
	wstring GetBubbleTypeToWString(BubbleType type) { return bubbles[0]->GetBubbleTypeToWString(type); }


private:
	int tag = 0;
	int maxBubbleCount = 0;
	int curBubbleCount = 0;

	int jetCount = 0;

	TileMap* map;

	vector<Bubble*> bubbles;
};