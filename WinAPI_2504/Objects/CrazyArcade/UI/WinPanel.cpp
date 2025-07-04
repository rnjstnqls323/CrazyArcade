#include "Framework.h"

WinPanel::WinPanel()
{
	CreateBackGround();
}

WinPanel::~WinPanel()
{
}

void WinPanel::Update(Player* player)
{
	timer += DELTA;
	if (timer >= SHOW_TIME)
	{
		UIManager::Get()->PopForntPanel();
		//씬옮기는거 해주자
	}
}

void WinPanel::Render()
{
	backGround->Render();
}
void WinPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Win/WinPannel.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}
