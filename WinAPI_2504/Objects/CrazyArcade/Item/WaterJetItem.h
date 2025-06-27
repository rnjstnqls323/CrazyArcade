#pragma once

class WaterJetItem : public Item
{
public:
	WaterJetItem();
	~WaterJetItem();

private:
	// Item을(를) 통해 상속됨
	void PlayerGetItem(Player* player) override;

};