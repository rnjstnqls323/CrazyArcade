#pragma once

class BuyCheckPanel :public Panel
{
public:
	BuyCheckPanel();
	~BuyCheckPanel();

private:
	// Panel을(를) 통해 상속됨
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;

	void OnClickYes();
	void OnClickNo();
	void SetInformation(BuyItem* itemData) { this->itemData = itemData; this->itemData; }
	void Reset() override {}

private:
	BuyItem* itemData;
};