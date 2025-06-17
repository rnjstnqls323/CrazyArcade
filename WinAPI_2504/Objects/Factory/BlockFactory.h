#pragma once

struct BlockData
{
	Quad* image;
	vector<Matrix> world;
	VertexBuffer* instanceBuffer;
};
enum BlockCategory
{
	Block1, Block2, Flower1, Flower2, Shell1, Shell2
};
class BlockFactory :public Singleton<BlockFactory>
{
	friend class Singleton;

private:
	BlockFactory();
	~BlockFactory();

public:
	void AddBlock(BlockCategory key, Vector2 pos); // �̰� �����ϸ� ������ instanceBuffer ������Ʈ�ؾߵ�
	void PopBlock(BlockCategory key, Vector2 pos); // �̰� �����ϸ� ������ instanceBuffer ������Ʈ�ؾߵ�

	void Render();

private:
	void Update();

	void CreateBlockInstances();

private:
	unordered_map<BlockCategory, BlockData*> blockInstances;
	//���ϰ�ο� �ִ� png�� �˾Ƽ� ���������� �ұ�
};