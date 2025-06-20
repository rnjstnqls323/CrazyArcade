#pragma once

enum WaterJetStatus
{
	LeftWater, RightWater, UpWater, DownWater
};

class WaterJet :public GameObject
{
public:
	WaterJet(Animation* animation);
	~WaterJet();

	void Render() override;
	void Update();

	Transform* GetTransform() { return transform; }

	void PlayAnimation() { animation->Play(0); }
	
	void SetIndex(Index2 index) { this->index = index; }
	Index2 GetIndex() { return index; }
private:
	void MakeMesh() override {}
private:

	Index2 index;
	Animation* animation; // 복사해서 써줄거임
	Transform* transform;
	MatrixBuffer* worldBuffer;

};