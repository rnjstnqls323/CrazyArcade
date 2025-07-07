#include "Framework.h"
#include "Stage1Scene.h"

Stage1Scene::Stage1Scene()
{
	curStatus = Stage1;
	CreatePlayerMap();
}

Stage1Scene::~Stage1Scene()
{
}

void Stage1Scene::Start()
{
	Audio::Get()->Play("bg_Stage1");
	PlayScene::Start();
}

void Stage1Scene::End()
{
	Audio::Get()->Stop("bg_Stage1");
	PlayScene::End();
}

void Stage1Scene::StopAudio()
{
	if (UIManager::Get()->GetFrontPanelType() != PanelType::PlayPanel)
	{
		Audio::Get()->Stop("bg_Stage1");
		isStop = true;
	}
	else if (isStop)
	{
		Audio::Get()->Play("bg_Stage1");
	}
}

void Stage1Scene::CreatePlayerMap()
{
	map = new TileMap("Stage1.map");
	player = new Player();
}
