#pragma once

enum WaterJet
{
	LeftWater, RightWater, UpWater, DownWater
}; //이거배열로할거라 이제 굳이 필요할까?

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
	// GameObject을(를) 통해 상속됨
	void MakeMesh() override {};
	void LoadAnimation();

private:
	int curLenght = 1;

	Transform* bubbleTransform;
	Animation* animation;
	unordered_map<WaterJet, RectCollider*> waterJets;
	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;
	// Idle일때만 animation 출력하자
};