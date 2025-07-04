#include "Framework.h"

LosePanel::LosePanel()
{
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
		//씬옮기는거 해주자
	}
}

void LosePanel::Render()
{
	backGround->UpdateWorld();
}
void LosePanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/Lose/LosePannel.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

