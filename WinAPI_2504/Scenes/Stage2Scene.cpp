#include "Framework.h"
#include "Stage2Scene.h"

Stage2Scene::Stage2Scene()
{
	curStatus = Stage2;
	CreatePlayerMap();
	audioKey = "bg_Stage2";
}

Stage2Scene::~Stage2Scene()
{
}
void Stage2Scene::CreatePlayerMap()
{
	map = new TileMap("Stage2.map");
	player = new Player();  
}
