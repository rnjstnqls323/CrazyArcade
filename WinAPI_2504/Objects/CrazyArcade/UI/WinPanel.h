#pragma once

class WinPanel :public Panel
{
private:
	const float SHOW_TIME = 5.0f;
public:
	WinPanel();
	~WinPanel();

	void Update(Player* player) override;
	void Render() override;

	void Reset();
private:

	void MakeMesh() override {}
	void CreateButtons() override {}
	void CreateBackGround() override;
	void SetEventFunc() override {}

private:
	float timer = 0.0f;
};