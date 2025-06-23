#pragma once

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
	void SetIsRender(bool isRender) { this->isRender = isRender; }

	Index2 GetIndex() { return index; }
	bool IsRender() { return isRender; }

private:
	void MakeMesh() override {}
private:
	bool isRender = false;
	Index2 index;
	Animation* animation; // 복사해서 써줄거임
	Transform* transform;
	MatrixBuffer* worldBuffer;

};