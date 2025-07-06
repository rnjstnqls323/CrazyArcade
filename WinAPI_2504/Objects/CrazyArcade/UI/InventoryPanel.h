#pragma once

struct ShowSetItem
{
	Quad* back;
	Quad* front;
};
class InventoryPanel : public Panel
{
public:
	InventoryPanel();
	~InventoryPanel();

	void Update(Player* player) override;
	void Render() override;
	
	void Reset() override {} //¿Ã∞≈∞ÌπŒ
private:
	void CreateShowSetItem();
	void ChangeShowItemFront(ShowItemStatus type);
	
	void CreateButtons() override;
	void CreateBackGround() override;
	void SetEventFunc() override;

	void OnClickCloseButton();
	void OnClickItemButton(ShowItemStatus status);
	void OnClickItemSetting();
	void OnClickItemSetOff();

	void AddItem(BuyItem* item);

private:
	wstring path = L"Resources/Textures/CrazyArcade_UI/Inventory/";
	unordered_map<ShowItemStatus,ShowSetItem> showSetItem;
	PlayerItem* itemPanel;
};