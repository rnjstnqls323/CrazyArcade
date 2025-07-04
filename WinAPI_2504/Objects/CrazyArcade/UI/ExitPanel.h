#pragma once

class ExitPanel :public Panel
{
public:
	ExitPanel();
	~ExitPanel();

private:
	void SetEventFunc() override;
	void CreateButtons() override;
	void CreateBackGround() override;

	void OutButton();
	void BackButton();
	void Reset() override {}
};