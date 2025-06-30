#pragma once

class PlayPanel : public Panel
{
public:
	PlayPanel();
	~PlayPanel();

	void Update(Player* player) override;
	void Render() override;

private:
	void MakeMesh() override {}
	void CreateButton() override;
	void CreateBackGround() override;
	void CreatePlayerAndNeedle();
	void SetEventFunc() override;

	void OutButton();

private:
	Quad* player;
	Quad* needle;
	//Quad* backGround;
};