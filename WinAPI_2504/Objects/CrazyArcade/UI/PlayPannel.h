#pragma once

class PlayPannel : public Pannel
{
public:
	PlayPannel();
	~PlayPannel();

	void Update() override;
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