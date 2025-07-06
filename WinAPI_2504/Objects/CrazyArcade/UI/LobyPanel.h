#pragma once

class LobyPanel :public Panel
{
public:
	LobyPanel();
	~LobyPanel();

	void Update(Player* player) override;
	void Render() override;

private:
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;
	void CreateCharacterButton();
	void CreatePlayerAndSelectPanel();

	void OnClickStartButton();
	void OnClickExitButton();
	void OnClickItemShopButton();
	void OnClickInventoryButton();
	void OnClickCharacterButton(CharacterName name);
private:

	wstring path = L"Resources/Textures/CrazyArcade_UI/Loby/";

	PlayerBackGround* playerBG;
	Quad* player;
	Quad* selectPlayerPanel;


	unordered_map<CharacterName, Button*> characterButton;
};