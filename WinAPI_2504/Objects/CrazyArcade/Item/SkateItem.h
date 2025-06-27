#pragma once

class SkateItem :public Item
{
public:
	SkateItem();
	~SkateItem();

private:
	// Item을(를) 통해 상속됨
	void PlayerGetItem(Player* player) override;

};