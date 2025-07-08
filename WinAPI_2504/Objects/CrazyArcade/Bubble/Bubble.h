#pragma once

enum WaterJetStatus
{
	LeftWater, RightWater, UpWater, DownWater
};

enum BubbleStatus
{
	BubbleIdle, Exploding, Dead
};
enum class BubbleType
{
	Basic, Bling, Dark, DarkStar, Punk, Korea, Rainbow, RedDevil, RedPang
};
class Bubble : public GameObject
{
private:
	const int MAX_JET_LENGTH = 5;
	const float BOMB_TIME = 2.0f;
	const float EXPLOING_TIME = 0.6f;

public:
	Bubble();
	~Bubble();

	void Render();
	void Update();
	void Spawn(Vector2 spawnPos,Index2 index, TileMap* map, int tag);

	BubbleType GetBubbleType() { return bubble; }
	void SetBubbleType(BubbleType type) { bubble = type; }

	BubbleStatus GetStatus() { return curStatus; }
	int GetTag() { return tag; }
	Index2 GetBubbleIndex() { return index; }

	void SetTag(int num) { tag = num; }
	void SetBombTime() { timer = BOMB_TIME; }
	

	void Reset();
	void AddLength() 
	{
		if (curLength < MAX_JET_LENGTH)
			curLength++;
	} 
	void MaxLength(){	curLength = MAX_JET_LENGTH;	}

	void SetJetLength(int length) { this->curLength = length; }
	void SetJetMaxLength() { this->curLength = MAX_JET_LENGTH; }

	string GetBubbleTypeToString(BubbleType type);
	wstring GetBubbleTypeToWString(BubbleType type);

private:
	void MakeMesh() override {}; 

	void LoadAnimation();
	
	void UpdateStatus();
	
	void CreateJet();
	void RenderJet();
	void UpdateJet();
	void SetIndexJet(Index2 index);

	bool IsBlockingTile(Index2 index);
	void CrushOrBomb();

private:
	int tag = 0;
	int curLength = 0;
	double timer = 0.0f;

	static BubbleType bubble;

	TileMap* map;
	Index2 index;
	Transform* bubbleTransform;
	unordered_map< BubbleType,Animation*> animation;

	unordered_map<WaterJetStatus, vector<WaterJet*>> waterJets; 
	
	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;

	MatrixBuffer* testBuffer;
	Transform* testTransform;
};