#pragma once

enum WaterJet
{
	LeftWater, RightWater, UpWater, DownWater
};
enum BubbleStatus
{
	Idle, Exploding, Dead
};
class Bubble
{
private:
	const int MAX_JET_LENGHT = 10;

public:
	Bubble();
	~Bubble();

private:
	int curLenght = 1;

	RectCollider* bubble;
	Animation* animation;
	unordered_map<WaterJet, RectCollider*> waterJets;
	BubbleStatus curStatus = Dead; // Idle일때만 animation 출력하자
};