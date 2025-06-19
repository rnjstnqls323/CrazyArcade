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
	Animation* jetAnimation; // 이건 복사  
	Transform* jetTransform;// 이건 할당
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
	unordered_map<WaterJet, Animation*> middleWaterJetAnimation;
	unordered_map<WaterJet, Animation*> endWaterJetAnimation;
	unordered_map<WaterJet, vector<Transform*>> waterJets; //물줄기 위치마다 셋팅해주자 풀링으로만들어놓고

	BubbleStatus curStatus = Dead;

	MatrixBuffer* worldBuffer;
	// Idle일때만 animation 출력하자
};