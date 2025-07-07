#include "Framework.h"

LosePanel::LosePanel()
{
	type = PanelType::LosePanel;
	CreateBackGround();
}

LosePanel::~LosePanel()
{
}

void LosePanel::Update(Player* player)
{
	timer += DELTA;
	if (timer >= SHOW_TIME)
	{
		Player::SetLucci(Player::GetLucci() + ADD_LOSE_LUCCI);
		UIManager::Get()->PopForntPanel();
		SCENE->ChangeScene("Loby");
	}
}
void LosePanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Lose/LosePannel.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

