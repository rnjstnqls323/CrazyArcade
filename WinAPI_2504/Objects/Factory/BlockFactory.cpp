#include "Framework.h"
#include "BlockFactory.h"

BlockFactory::BlockFactory()
{
	CreateBlockInstances();
}

BlockFactory::~BlockFactory()
{
}

void BlockFactory::AddBlock(BlockCategory key, Vector2 pos)
{
}

void BlockFactory::PopBlock(BlockCategory key, Vector2 pos)
{
}

void BlockFactory::Render()
{
}

void BlockFactory::Update()
{
}

void BlockFactory::CreateBlockInstances()
{
	blockInstances[Block1]->image = new Quad(L"");//경로 적기 이런식으로 싹 초기화해주기
}
