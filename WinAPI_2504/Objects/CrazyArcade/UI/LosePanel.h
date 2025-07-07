#pragma once

class LosePanel : public Panel
{
private:
	const float SHOW_TIME = 5.0f;
	const int ADD_LOSE_LUCCI = 2000;
public:
	LosePanel();
	~LosePanel();

	void Update(Player* player) override;
	void Reset() override { timer = 0.0f; }
private:
	void CreateButtons() override {}
	void CreateBackGround() override;
	void SetEventFunc() override {}


private:
	float timer = 0.0f;
};