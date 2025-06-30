#pragma once

class ExitPanel :public Panel
{
public:
	ExitPanel();
	~ExitPanel();

	void Render() override;
	void Update(Player* player) override;

private:
	void SetEventFunc() override;
	void MakeMesh() override {}
	void CreateButtons() override;
	void CreateBackGround() override;

	void OutButton();
	void BackButton();
};