#pragma once

class PlayPanel : public Panel
{
public:
	PlayPanel();
	~PlayPanel();

	void Update(Player* player) override;
	void Render() override;

private:
	void CreateButtons() override;
	void CreateBackGround() override;
	void CreatePlayerAndNeedle();
	void SetEventFunc() override;

	void OutButton();

private:
	bool isNeedle = false;
	PlayerViewSmall* player;
	Quad* needle;
	//Quad* backGround;
};