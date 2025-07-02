#include "Framework.h"

PlayerItem::PlayerItem()
{
    SetLocalPosition(Vector2{CENTER_X-200,CENTER_Y+50});
    UpdateWorld();
    CreateBubble();
    CreateBackGround();

    backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Inventory/Panel.png");
    backGround->SetParent(this);
    backGround->UpdateWorld();

    SetEventFunc();
}

PlayerItem::~PlayerItem()
{
    for (auto& backGround : showBackGround)
    {
        delete backGround.second;
    }
    showBackGround.clear();
}

void PlayerItem::Update()
{
    switch (curStatus)
    {
    case ShowItemStatus::None:
        return;
    case ShowItemStatus::Bubble:
        return;
    case ShowItemStatus::BackGround:
        BackGroundUpdate();
        break;
    }
}

void PlayerItem::Render()
{
    switch (curStatus)
    {
    case ShowItemStatus::None:
        return;
    case ShowItemStatus::Bubble:
        return;
    case ShowItemStatus::BackGround:
        BackGroundRender();
        break;
    }
}

bool PlayerItem::InsertBubble(BubbleType type)
{
    if(inventoryBubble.count(type)) return false;
    
    inventoryBubble.insert(type);
    return true;
}

bool PlayerItem::InsertBackGround(PlayerBackGroundType type)
{
    if (inventoryBackGround.count(type)) return false;

    inventoryBackGround.insert(type);
    int num = inventoryBackGround.size() - 1;
    int col = 4;
    Vector2 pos = { startPos.x + (num % col) * addPos.x , startPos.y + (num / col) * addPos.y };
    showBackGround[type]->SetParent(this);
    showBackGround[type]->SetLocalPosition(pos);
    showBackGround[type]->UpdateWorld();

    return true;
}

void PlayerItem::SetBasic()
{
    choiceType.backGroundType = PlayerBackGroundType::Basic;
    choiceType.bubbleType = BubbleType::Basic;
}

wstring PlayerItem::GetShowItemStatusToWString(ShowItemStatus status)
{
    switch (status)
    {
    case ShowItemStatus::Bubble:
        return L"Bubble";
    case ShowItemStatus::BackGround:
        return L"BackGround";
    case ShowItemStatus::ShaShak:
        return L"ShaShak";
    }
}

void PlayerItem::SetEventFunc()
{
    for (auto& backGround : showBackGround)
    {
        PlayerBackGroundType key = backGround.first;
        backGround.second->SetOnClick([this, key]() {OnClickBackGroundButton(key);});
    }
}

void PlayerItem::BubbleRender()
{
}

void PlayerItem::BackGroundRender()
{
    backGround->Render();
    for (PlayerBackGroundType type : inventoryBackGround)
    {
        showBackGround[type]->Render();
    }
}

void PlayerItem::BubbleUpdate()
{
}

void PlayerItem::BackGroundUpdate()
{
    for (PlayerBackGroundType type : inventoryBackGround)
    {
        showBackGround[type]->Update();
    }
}

void PlayerItem::CreateBubble()
{

}

void PlayerItem::CreateBackGround() //여기서 애초에 위치를 잡을 필요가없네
{
    Vector2 size = Vector2{ 80,80 };
    wstring path = L"Item/BackGround/";
    for (int i = 0;i < (int)PlayerBackGroundType::Hopi;i++)
    {
        PlayerBackGroundType type = (PlayerBackGroundType)(i + 1);
        wstring name = PlayerBackGround::GetBackGroundTypeToWString(type);
        showBackGround[type] = new Button(path+name, startPos, size);
    }
}

void PlayerItem::OnClickBackGroundButton(PlayerBackGroundType type)
{
    choiceType.backGroundType = type;
}

