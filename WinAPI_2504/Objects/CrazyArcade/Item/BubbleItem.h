#pragma once

class BubbleItem :public Item
{
public:
	BubbleItem();
	~BubbleItem();

private:
	void PlayerGetItem(Player* player) override;
};