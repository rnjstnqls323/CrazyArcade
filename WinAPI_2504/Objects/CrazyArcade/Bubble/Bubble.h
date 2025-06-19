#pragma once

enum WaterJet
{
	LeftWater, RightWater, UpWater, DownWater
}; 
enum BubbleStatus
{
	BubbleIdle, Exploding, Dead
};
struct JetSegment
{
	Animation* jetAnimation; // �̰� ����  
	Transform* jetTransform;// �̰� �Ҵ�
};
class Bubble : public GameObject
{
private:
	const int MAX_JET_LENGHT = 10;

public:
	Bubble();
	~Bubble();

	void Render();
	void Update();
	void Spawn(Vector2 spawnPos);

	void Reset();
private:
	// GameObject��(��) ���� ��ӵ�
	void MakeMesh() override {};
	void LoadAnimation();

private:
	int curLenght = 1;

	Transform* bubbleTransform;
	Animation* animation;
	unordered_map<WaterJet, Animation*> middleWaterJetAnimation;
	unordered_map<WaterJet, Animation*> endWaterJetAnimation;
	unordered_map<WaterJet, vector<Transform*>> waterJets; //���ٱ� ��ġ���� ���������� Ǯ�����θ�������

	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;
	// Idle�϶��� animation �������
};