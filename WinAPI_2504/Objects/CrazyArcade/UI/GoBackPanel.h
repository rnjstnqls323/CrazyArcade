#pragma once

class GoBackPanel :public Panel
{
public:
	GoBackPanel();
	~GoBackPanel();

private:
	// Panel을(를) 통해 상속됨
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;

	void OnClickYesButton();
	void OnClickNoButton();
	void Reset() override {}
};