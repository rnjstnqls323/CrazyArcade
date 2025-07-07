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

void Stage2Scene::CreatePlayerMap()
{
	map = new TileMap("TestStage1.map");
	player = new Player();
}
