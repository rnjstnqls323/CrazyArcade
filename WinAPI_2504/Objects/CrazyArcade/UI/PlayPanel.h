#pragma once

class PlayPanel : public Panel
{
public:
	PlayPanel();
	~PlayPanel();

	void Update(Player* player) override;
	void Render() override;
	void Reset() override;
private:
	void CreateButtons() override;
	void CreateBackGround() override;
	void CreatePlayerAndNeedle();
	void CreateTimer();

	void ChangeTime();
	void SetEventFunc() override;

	void OutButton();
	
private:
	wstring path = L"Resources/Textures/CrazyArcade_UI/Play/";
	float leftTime = 180.0f;
	float timer = 1.0f;
	bool isNeedle = false;
	PlayerViewSmall* player;
	Quad* needle;
	vector<Quad*> showTime;
	//Quad* backGround;
};