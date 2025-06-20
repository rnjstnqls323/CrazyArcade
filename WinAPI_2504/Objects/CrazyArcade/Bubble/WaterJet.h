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
	Animation* animation; // �����ؼ� ���ٰ���
	Transform* jetTransform;
	//�̰� ��ü�ϳ��� �ƿ� �����¿�� ���� ���� �̰� �����ϱ� �����
};