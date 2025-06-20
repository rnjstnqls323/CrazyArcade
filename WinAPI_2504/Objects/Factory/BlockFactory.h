#pragma once

struct BlockData
{
	Quad* image;
	vector<Matrix> blockWorld;
	VertexBuffer* instanceBuffer;
};
enum BlockCategory
{
	Block1, Block2, Flower1, Flower2, Shell1, Shell2, BlockCatecoryEnd
};
class BlockFactory :public Singleton<BlockFactory>
{
	friend class Singleton;

private:
	const int MAX_BLOCK_NUM = 100;
private:
	BlockFactory();
	~BlockFactory();

public:
	void AddBlock(BlockCategory key, Vector2 pos); // 이거 실행하면 무조건 instanceBuffer 업데이트해야됨
	void PopBlock(BlockCategory key, Vector2 pos); // 이거 실행하면 무조건 instanceBuffer 업데이트해야됨

	void Render();

	void CreateInstanceBuffer();

private:
	void CreateBlockInstances();
	void CreateMap();

private:

	unordered_map<BlockCategory, BlockData*> blockInstances;
	//파일경로에 있는 png로 알아서 만들어버리게 할까
};