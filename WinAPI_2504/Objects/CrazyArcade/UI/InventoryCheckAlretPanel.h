#pragma once

class InventoryCheckAlretPanel :public Panel
{
public:
	InventoryCheckAlretPanel();
	~InventoryCheckAlretPanel();
private:


	// Panel을(를) 통해 상속됨
	void CreateButtons() override;

	void CreateBackGround() override;

	void SetEventFunc() override;

};