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

void Stage1Scene::CreatePlayerMap()
{
	map = new TileMap("Stage1.map");
	player = new Player();
}
