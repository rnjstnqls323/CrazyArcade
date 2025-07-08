#include "Framework.h"

WinPanel::WinPanel()
{
	type = PanelType::WinPanel;
	CreateBackGround();
}

WinPanel::~WinPanel()
{
}

void WinPanel::Update(Player* player)
{
	timer += DELTA;
	if (timer >= SHOW_TIME )
	{
		player->SetLucci(player->GetLucci()+ADD_WIN_LUCCI);
		UIManager::Get()->PopForntPanel();
		EventManager::Get()->ExcuteEvent("ChangeStage",nullptr);
	}
}
void WinPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Win/WinPannel.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}
