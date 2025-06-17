#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	BlockFactory::Get();
	map = new TileMap("Resources/TextData/TestStage1.map");
}

TestScene::~TestScene()
{
	BlockFactory::Delete();
	delete map;
}

void TestScene::Update()
{
}

void TestScene::Render()
{
	map->Render();
	BlockFactory::Get()->Render();
}
