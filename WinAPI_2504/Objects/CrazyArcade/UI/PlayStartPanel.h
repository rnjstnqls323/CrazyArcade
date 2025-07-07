#pragma once

class PlayStartPanel :public Panel
{
private:
	const float SHOW_TIME = 3.0f;
public:
	PlayStartPanel();
	~PlayStartPanel();

	void Reset();
	void Update(Player* player) override;
private:
	void CreateButtons() override {}
	void CreateBackGround() override;
	void SetEventFunc() override {}

private:
	float timer = 0.0f;
};