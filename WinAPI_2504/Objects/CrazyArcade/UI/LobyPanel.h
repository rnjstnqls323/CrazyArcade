#pragma once

class LobyPanel :public Panel
{
public:
	LobyPanel();
	~LobyPanel();

	void Update(Player* player) override;
	void Render() override;

private:
	void MakeMesh() override {}
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;
	void CreateCharacterButton();

	void OnClickStartButton();
	void OnClickExitButton();
	void OnClickItemShopButton();
	void OnClickInventoryButton();
	void OnClickCharacterButton(CharacterName name);
private:
	PlayerBackGround* playerBG;
	Quad* player;
	unordered_map<CharacterName, Button*> characterButton;
};