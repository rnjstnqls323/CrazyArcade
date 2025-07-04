#pragma once

struct BuyItem
{
	ShowItemStatus status;
	BubbleType bubbleType;
	PlayerBackGroundType backGroundType;
	ShaShakType shaShakType;
	//»þ¼¡ ³Ö±â
};
class StorePanel :public Panel
{
public:
	StorePanel();
	~StorePanel();

	void Update(Player* player) override;
	void Render() override;
private:
	void CreateButtons() override;
	void CreateBackGround() override;
	void CreateShowLucci();
	void CreateChoiceItem();
	void SetEventFunc() override;

	void OnClickExit();
	void OnClickGoBack();
	void OnClickItem(ShowItemStatus status);
	void OnClickTest();
	void OnClickSet();

	void ChangeLucci(int lucci);
	void ChangeCoiceItem();
	void SavePreType();
	void SettingItem();

	void SetBuyItem();

	void Reset() override {}
private:
	bool isSavePreType = false;
	bool isChoice = false;
	int lucci;
	wstring path = L"Resources/Textures/CrazyArcade_UI/Store/";

	ChoiceItemType preType;
	ChoiceItemType preChoiceType;

	BuyItem buyItem;

	PlayerBackGround* testBackGround;

	PlayerItem* item;
	vector<Quad*> showLucci;
	Quad* choiceItem;
};