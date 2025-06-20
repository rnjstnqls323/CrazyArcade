#pragma once


enum BubbleStatus
{
	BubbleIdle, Exploding, Dead
};
struct JetSegment
{
	Animation* jetAnimation; //이건 복사
	Transform* jetTransform; //이건 할당
	MatrixBuffer* jetWorldBuffer; //이건 고민 좀 해보자 프레임수보고 고민 ㄱㄱ
	bool isJetActive = false;
};
class Bubble : public GameObject
{
private:
	const int MAX_JET_LENGTH = 5;
	const float BOMB_TIME = 2.0f;
	const float EXPLOING_TIME = 1.0f;

public:
	Bubble();
	~Bubble();

	void Render();
	void Update();
	void Spawn(Vector2 spawnPos);

	BubbleStatus GetStatus() { return curStatus; }
	int GetTag() { return tag; }

	void SetTag(int num) { tag = num; }


	void Reset();
	void AddLength() 
	{
		if (curLength < MAX_JET_LENGTH)
			curLength++;
	} //이거보다 매니저가 한번에 관리하는게 훨씬 간단하겠는데?
private:
	void MakeMesh() override {}; 

	void LoadAnimation();
	void LoadWaterJetAnimation();
	
	void UpdateStatus();
	
	void CreateJet();
	void RenderJet();
	void UpdateJet();

private:
	int tag = 0;
	int curLength = 1;
	double timer = 0.0f;

	Transform* bubbleTransform;
	Animation* animation;

	unordered_map<WaterJetStatus, Animation*> waterJetAnimation; //이거 걍 클립으로받을까
	unordered_map<WaterJetStatus, vector<JetSegment*>> waterJets; 
	//물줄기 위치마다 셋팅해주자 풀링으로만들어놓고 노노 물줄기 걍 객체로 빼자

	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;

	MatrixBuffer* testBuffer;
	Transform* testTransform;
};