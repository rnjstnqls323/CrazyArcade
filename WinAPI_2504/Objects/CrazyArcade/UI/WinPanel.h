#pragma once

class WinPanel :public Panel
{
private:
	const float SHOW_TIME = 5.0f;
	const int ADD_WIN_LUCCI = 3200;
public:
	WinPanel();
	~WinPanel();

	void Update(Player* player) override;
	void Reset() override { timer = 0.0f; }
private:
	void CreateButtons() override {}
	void CreateBackGround() override;
	void SetEventFunc() override {}
private:
	float timer = 0.0f;
};