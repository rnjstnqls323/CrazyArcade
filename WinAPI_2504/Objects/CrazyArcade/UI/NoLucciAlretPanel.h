#pragma once

class NoLucciAlretPanel :public Panel
{
public:
	NoLucciAlretPanel();
	~NoLucciAlretPanel();

private:
	// Panel을(를) 통해 상속됨
	void CreateButtons() override;

	void CreateBackGround() override;

	void SetEventFunc() override;
	void Reset() override {}

	void OnClickYes();

};