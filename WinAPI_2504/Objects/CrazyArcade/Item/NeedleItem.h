#pragma once

class NeedleItem :public Item
{
public:
	NeedleItem();
	~NeedleItem();

private:
	// Item을(를) 통해 상속됨
	void PlayerGetItem(Player* player) override;

};