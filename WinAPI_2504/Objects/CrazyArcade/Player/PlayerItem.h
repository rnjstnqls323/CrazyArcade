#pragma once

enum class ShowItemStatus
{
	None, Bubble, BackGround, ShaShak
};
struct ChoiceItemType
{
	BubbleType bubbleType = BubbleType::Basic;
	PlayerBackGroundType backGroundType = PlayerBackGroundType::Basic;
	ShaShakType shaShakType  = ShaShakType::Basic;
};
class PlayerItem : public Transform
{
public:
	PlayerItem();
	~PlayerItem();

	void Update();
	void Render();

	bool InsertBubble(BubbleType type);
	bool InsertBackGround(PlayerBackGroundType type);
	bool InsertShaShak(ShaShakType type);

	void ChaingeCurStatus(ShowItemStatus status) { curStatus = status; }
	ShowItemStatus GetCurStatus() { return curStatus; }

	void SetBasic(ShowItemStatus status);
	ChoiceItemType GetItemType() { return choiceType; }

	wstring GetShowItemStatusToWString(ShowItemStatus status);

	void ItemUpdateWorld() { UpdateWorld();backGround->UpdateWorld();}

private:
	void SetEventFunc();
	void BubbleRender();
	void BackGroundRender();
	void ShaShakRender();

	void BubbleUpdate();
	void BackGroundUpdate();
	void ShaShakUpdate();

	void CreateBubble();
	void CreateBackGround();
	void CreateShaShak();

	void OnClickBackGroundButton(PlayerBackGroundType type);
	void OnClickBubbleButton(BubbleType type);
	void OnClickShaShakButton(ShaShakType type);

private:
	Quad* backGround;
	Vector2 startPos = {-170,125 };
	Vector2 addPos = { 110,-110 };

	ShowItemStatus curStatus = ShowItemStatus::None;

	ChoiceItemType choiceType;

	unordered_set<BubbleType> inventoryBubble;
	unordered_set<PlayerBackGroundType> inventoryBackGround;
	unordered_set<ShaShakType> inventoryShaShak;

	unordered_map <BubbleType, Button*> showBubble;
	unordered_map <PlayerBackGroundType, Button*> showBackGround;
	unordered_map <ShaShakType, Button*> showShaShak;
};