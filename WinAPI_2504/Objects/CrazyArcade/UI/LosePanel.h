#pragma once

class LosePanel : public Panel
{
private:
	const float SHOW_TIME = 5.0f;
public:
	LosePanel();
	~LosePanel();

	void Update(Player* player) override;
	void Render() override;

private:
	void CreateButtons() override {}
	void CreateBackGround() override;
	void SetEventFunc() override {}

	void Reset() override {} //이거타이머초기화
private:
	float timer = 0.0f;
};