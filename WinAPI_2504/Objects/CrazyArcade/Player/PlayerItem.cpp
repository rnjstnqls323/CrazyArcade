#include "Framework.h"

PlayerItem::PlayerItem()
{
    SetLocalPosition(Vector2{CENTER_X-200,CENTER_Y+50});
    CreateBubble();
    CreateBackGround();
    CreateShaShak();
    UpdateWorld();

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
    for (auto& bubble : showBubble)
    {
        delete bubble.second;
    }
    showBubble.clear();
    for (auto& shashak : showShaShak)
    {
        delete shashak.second;
    }
    showShaShak.clear();
}

void PlayerItem::Update()
{
    //이거 계속 업데이트안해도된다. 상점에서 구매하면 업데이트되게하자
    switch (curStatus)
    {
    case ShowItemStatus::None:
        return;
    case ShowItemStatus::Bubble:
        BubbleUpdate();
        return;
    case ShowItemStatus::BackGround:
        BackGroundUpdate();
        return;
    case ShowItemStatus::ShaShak:
        ShaShakUpdate();
        return;
    }
}

void PlayerItem::Render()
{
    switch (curStatus)
    {
    case ShowItemStatus::None:
        return;
    case ShowItemStatus::Bubble:
        BubbleRender();
        return;
    case ShowItemStatus::BackGround:
        BackGroundRender();
        return;
    case ShowItemStatus::ShaShak:
        ShaShakRender();
        return;
    }
}

bool PlayerItem::InsertBubble(BubbleType type)
{
    if(inventoryBubble.count(type)) return false;
    
    inventoryBubble.insert(type);
    int num = inventoryBubble.size() - 1;
    int col = 4;
    Vector2 pos = { startPos.x + (num % col) * addPos.x , startPos.y + (num / col) * addPos.y };
    showBubble[type]->SetParent(this);
    showBubble[type]->SetLocalPosition(pos);
    showBubble[type]->UpdateWorld();
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
bool PlayerItem::InsertShaShak(ShaShakType type)
{
    if (inventoryShaShak.count(type)) return false;

    inventoryShaShak.insert(type);
    int num = inventoryShaShak.size() - 1;
    int col = 4;
    Vector2 pos = { startPos.x + (num % col) * addPos.x , startPos.y + (num / col) * addPos.y };
    showShaShak[type]->SetParent(this);
    showShaShak[type]->SetLocalPosition(pos);
    showShaShak[type]->UpdateWorld();

    return true;
}
void PlayerItem::SetBasic(ShowItemStatus status)
{
    switch (status)
    {
    case ShowItemStatus::Bubble:
        choiceType.bubbleType = BubbleType::Basic;
        break;
    case ShowItemStatus::BackGround:
        choiceType.backGroundType = PlayerBackGroundType::Basic;
        break;
    case ShowItemStatus::ShaShak:
        choiceType.shaShakType = ShaShakType::Basic;
        break;
    }
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
    for (auto& bubble : showBubble)
    {
        BubbleType key = bubble.first;
        bubble.second->SetOnClick([this, key]() {OnClickBubbleButton(key); });
    }
    for (auto& shaShak : showShaShak)
    {
        ShaShakType key = shaShak.first;
        shaShak.second->SetOnClick([this, key]() {OnClickShaShakButton(key); });
    }
}

void PlayerItem::BubbleRender()
{
    backGround->Render();
    for (BubbleType type : inventoryBubble)
    {
        showBubble[type]->Render();
    }
}

void PlayerItem::BackGroundRender()
{
    backGround->Render();
    for (PlayerBackGroundType type : inventoryBackGround)
    {
        showBackGround[type]->Render();
    }
}

void PlayerItem::ShaShakRender()
{
    backGround->Render();
    for (ShaShakType type : inventoryShaShak)
    {
        showShaShak[type]->Render();
    }
}

void PlayerItem::BubbleUpdate()
{
    for (BubbleType type : inventoryBubble)
    {
        showBubble[type]->Update();
    }
}

void PlayerItem::BackGroundUpdate()
{
    for (PlayerBackGroundType type : inventoryBackGround)
    {
        showBackGround[type]->Update();
    }
}

void PlayerItem::ShaShakUpdate()
{
    for (ShaShakType type : inventoryShaShak)
    {
        showShaShak[type]->Update();
    }
}

void PlayerItem::CreateBubble()
{
    Vector2 size = Vector2{ 80,80 };
    wstring path = L"Item/Bubble/";
    for (int i = 0; i < (int)BubbleType::RedPang; i++)
    {
        BubbleType type = (BubbleType)(i + 1);
        wstring name = BubbleManager::Get()->GetBubbleTypeToWString(type);
        showBubble[type] = new Button(path + name, startPos, size);
    }
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

void PlayerItem::CreateShaShak()
{
    Vector2 size = Vector2{ 80,80 };
    wstring path = L"Item/ShaShak/";
    for (int i = 0; i < (int)ShaShakType::Heart; i++)
    {
        ShaShakType type = (ShaShakType)(i + 1);
        wstring name = ShaShak::GetShaShakTypeToWString(type);
        showShaShak[type] = new Button(path + name, startPos, size);
    }
}

void PlayerItem::OnClickBackGroundButton(PlayerBackGroundType type)
{
    choiceType.backGroundType = type;
}

void PlayerItem::OnClickBubbleButton(BubbleType type)
{
    choiceType.bubbleType = type;
}

void PlayerItem::OnClickShaShakButton(ShaShakType type)
{
    choiceType.shaShakType = type;
}

