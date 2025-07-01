#pragma once

class InventoryPanel : public Panel
{
public:
	InventoryPanel();
	~InventoryPanel();

private:
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;

};