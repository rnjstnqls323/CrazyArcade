#pragma once


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
	void SetEventFunc() override;

	void OnClickExit();
	void OnClickGoBack();
	void OnClickItem(ShowItemStatus status);

	void ChangeLucci(int lucci);
	void SavePreType();
	void SettingItem();
private:
	bool isSavePreType = false;
	int lucci;
	wstring path = L"Resources/Textures/CrazyArcade_UI/Store/";

	ChoiceItemType preType;

	PlayerItem* item;
	vector<Quad*> showLucci;
};