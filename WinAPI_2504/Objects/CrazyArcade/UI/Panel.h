#pragma once

enum class PanelType {
	PlayPanel,ExitPanel,GoBackPanel, WinPanel,LosePanel, LobyPanel, InventoryPanel, StorePanel, BuyCheckPanel,
	NoLucciAlretPanel, InventoryCheckAlretPanel, NoChoiceAlretPanel
};
class Panel : public Transform
{
public:
	Panel();
	~Panel();

	virtual void Update(Player* player = nullptr);
	virtual void Render();
	void PanelEdit();

protected:
	virtual void CreateButtons() = 0;
	virtual void CreateButton(wstring fileName, Vector2 pos, Vector2 size);
	virtual void CreateBackGround() = 0;
	virtual void SetEventFunc() = 0;

	virtual void Reset() = 0;
protected:

	Vector2 pos = { 700, 480 };
	Quad* backGround;
	vector<Button*> buttons;
};