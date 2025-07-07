#include "Framework.h"
#include "Stage2Scene.h"

Stage2Scene::Stage2Scene()
{
	curStatus = Stage2;
	CreatePlayerMap();
}

Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Start()
{
	Audio::Get()->Play("bg_Stage2");
	PlayScene::Start();
}

void Stage2Scene::End()
{
	Audio::Get()->Stop("bg_Stage2");
	PlayScene::End();
}

void Stage2Scene::StopAudio()
{
}

void Stage2Scene::CreatePlayerMap()
{
	map = new TileMap("TestStage1.map");
	player = new Player();
}
