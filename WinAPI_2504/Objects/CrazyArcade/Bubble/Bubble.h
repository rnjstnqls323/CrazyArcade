#pragma once

enum WaterJet
{
	LeftWater, RightWater, UpWater, DownWater
}; //�̰Ź迭���ҰŶ� ���� ���� �ʿ��ұ�?

enum BubbleStatus
{
	BubbleIdle, Exploding, Dead
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
	unordered_map<WaterJet, RectCollider*> waterJets;
	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;
	// Idle�϶��� animation �������
};