#pragma once

class NoChoiceAlretPanel : public Panel
{
public:
	NoChoiceAlretPanel();
	~NoChoiceAlretPanel();
private:
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;

	void OnClickYes();

	void Reset() override {}
};