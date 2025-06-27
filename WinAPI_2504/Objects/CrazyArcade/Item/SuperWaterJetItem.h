#pragma once

class SuperWaterJetItem : public Item
{
public:
	SuperWaterJetItem();
	~SuperWaterJetItem();

private:
	// Item을(를) 통해 상속됨
	void PlayerGetItem(Player* player) override;

};