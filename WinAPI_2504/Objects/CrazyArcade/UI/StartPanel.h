#pragma once

class StartPanel :public Panel
{
public:
	StartPanel();
	~StartPanel();


private:
	void CreateButtons() override;
	void CreateBackGround() override;

	void OnClickMapEdit();
	void OnClickStart();

	void SetEventFunc() override;
};