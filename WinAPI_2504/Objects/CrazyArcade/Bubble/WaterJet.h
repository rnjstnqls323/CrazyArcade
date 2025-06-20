#pragma once

enum WaterJetStatus
{
	LeftWater, RightWater, UpWater, DownWater
};

class WaterJet :public GameObject
{
public:
	WaterJet();
	~WaterJet();

	void Update();
	void Render();

private:
	Animation* animation; // 복사해서 써줄거임
	Transform* jetTransform;
	//이거 객체하나를 아예 상하좌우로 빼자 ㅇㅇ 이게 관리하기 쉬울듯
};