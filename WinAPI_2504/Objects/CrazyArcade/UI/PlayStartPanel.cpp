#include "Framework.h"

PlayStartPanel::PlayStartPanel()
{
	CreateBackGround();
}

PlayStartPanel::~PlayStartPanel()
{
}

void PlayStartPanel::Reset()
{
	timer = 0.0f;
}

void PlayStartPanel::Update(Player* player)
{
	timer += DELTA;
	if (timer > SHOW_TIME)
	{
		EventManager::Get()->ExcuteEvent("StartStage", nullptr);
		UIManager::Get()->PopForntPanel();
	}
}

void PlayStartPanel::CreateBackGround()
{
	backGround = new Quad(L"Resources/Textures/CrazyArcade_UI/PlayStart/backGround.png");
	backGround->SetLocalPosition(pos);
	backGround->SetParent(this);
	backGround->UpdateWorld();
}

