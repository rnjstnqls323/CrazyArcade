#pragma once

enum class ItemType 
{
	BubbleItem, WaterJetItem, SuperWaterJetItem, SkateItem, NeedleItem, EndItem
};
class Item : public RectCollider // 시드 안심어놔서 랜덤으로는 못할 것 같고 그냥 순서대로 뽑아야될듯
{
public:
	Item();
	~Item();

	void Update();
	void Render();
	void SpawnItem(Vector2 pos);
	void CollisionPlayer(Player* player);
protected:
	void LoadAnimation();
	virtual void PlayerGetItem(Player* player) = 0;

protected:
	Animation* animation;
	MatrixBuffer* animationWorld;
	Transform* animationTransform;

	string path = "Resources/Textures/CrazyArcade_Item/";
};