#pragma once


enum BubbleStatus
{
	BubbleIdle, Exploding, Dead
};
struct JetSegment
{
	Animation* jetAnimation; //�̰� ����
	Transform* jetTransform; //�̰� �Ҵ�
	MatrixBuffer* jetWorldBuffer; //�̰� ��� �� �غ��� �����Ӽ����� ��� ����
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
	} //�̰ź��� �Ŵ����� �ѹ��� �����ϴ°� �ξ� �����ϰڴµ�?
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

	unordered_map<WaterJetStatus, Animation*> waterJetAnimation; //�̰� �� Ŭ�����ι�����
	unordered_map<WaterJetStatus, vector<JetSegment*>> waterJets; 
	//���ٱ� ��ġ���� ���������� Ǯ�����θ������� ��� ���ٱ� �� ��ü�� ����

	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;

	MatrixBuffer* testBuffer;
	Transform* testTransform;
};