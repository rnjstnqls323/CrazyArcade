#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	map = new TileMap("Resources/TextData/TestStage1.map");
}

TestScene::~TestScene()
{
	delete map;
}

void TestScene::Update()
{
}

void TestScene::Render()
{
	map->Render();
}
