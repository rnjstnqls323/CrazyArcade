#pragma once

enum WaterJetStatus
{
	LeftWater, RightWater, UpWater, DownWater
};

enum BubbleStatus
{
	BubbleIdle, Exploding, Dead
};

class Bubble : public GameObject
{
private:
	const int MAX_JET_LENGTH = 5;
	const float BOMB_TIME = 2.0f;
	const float EXPLOING_TIME = 0.8f;

public:
	Bubble();
	~Bubble();

	void Render();
	void Update();
	void Spawn(Vector2 spawnPos,Index2 index, TileMap* map, int tag);

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

private:
	void MakeMesh() override {}; 

	void LoadAnimation();
	void LoadWaterJetAnimation();
	
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

	TileMap* map;
	Index2 index;
	Transform* bubbleTransform;
	Animation* animation;

	unordered_map<WaterJetStatus, Animation*> waterJetAnimation; //클립으로 뺄까
	unordered_map<WaterJetStatus, vector<WaterJet*>> waterJets; 
	
	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;

	MatrixBuffer* testBuffer;
	Transform* testTransform;
};