#include "Framework.h"
#include "BlockFactory.h"

BlockFactory::BlockFactory()
{
	CreateBlockInstances();
}

BlockFactory::~BlockFactory()
{

	for (auto& pair : blockInstances)
	{
		delete pair.second->image;
		pair.second->blockWorld.clear();

		if(pair.second->instanceBuffer != nullptr)
			delete pair.second->instanceBuffer;
		delete pair.second;
	}
}

void BlockFactory::AddBlock(BlockCategory key, Vector2 pos)
{
	Matrix world = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	world = XMMatrixTranspose(world);

	blockInstances[key]->blockWorld.push_back(world); 	
}

void BlockFactory::PopBlock(BlockCategory key, Vector2 pos)
{
	auto& world = blockInstances[key]->blockWorld;

	for (size_t i = 0; i < world.size(); ++i)
	{
		XMFLOAT4X4 mat;
		XMStoreFloat4x4(&mat, world[i]);

		Vector2 matrixPos(mat._41, mat._42);

		if (matrixPos == pos)
		{
			world.erase(world.begin() + i);
			break;
		}
	}

	blockInstances[key]->instanceBuffer->Update(blockInstances[key]->blockWorld.data(), blockInstances[key]->blockWorld.size()); //지우고 바로 업데이트
}

void BlockFactory::Render()
{

	for (auto& data : blockInstances)
	{
		if (data.second->blockWorld.size() <= 0)
			continue;
	
		data.second->instanceBuffer->Set(1);
		
		data.second->image->GetMaterial()->Set();
		data.second->image->GetMesh()->DrawInstanced(data.second->blockWorld.size());
	}
}

void BlockFactory::CreateInstanceBuffer()
{
	for (auto& data : blockInstances)
	{
		if (data.second->blockWorld.size() <= 0)
			continue;

		if (data.second->instanceBuffer == nullptr)
		{
			data.second->instanceBuffer = new VertexBuffer(data.second->blockWorld.data(), sizeof(Matrix), MAX_BLOCK_NUM);
		}		
	}
}

void BlockFactory::CreateBlockInstances()
{
	CreateMap();

	wstring imagePath = L"Resources/Textures/CrazyArcade_BG_Texture/";
	blockInstances[Block1]->image = new Quad(imagePath + L"Block1.png");
	blockInstances[Block2]->image = new Quad(imagePath + L"Block2.png");
	blockInstances[Flower1]->image = new Quad(imagePath + L"Flower1.png");
	blockInstances[Flower2]->image = new Quad(imagePath + L"Flower2.png");
	blockInstances[Shell1]->image = new Quad(imagePath + L"Shell1.png");
	blockInstances[Shell2]->image = new Quad(imagePath + L"Shell2.png");

	for (auto& data : blockInstances)
	{
		data.second->image->GetMaterial()->SetShader(L"Instancing.hlsl");
	}
}

void BlockFactory::CreateMap()
{
	for (int i = 0;i < (int)BlockCatecoryEnd;i++)
	{
		blockInstances[(BlockCategory)i] = new BlockData();
	}
}
