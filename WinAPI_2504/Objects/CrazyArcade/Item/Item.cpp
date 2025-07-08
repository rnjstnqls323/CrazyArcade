#include "Framework.h"

Item::Item():RectCollider(Vector2(40,40))
{
	animation = new Animation;
	animationTransform = new Transform; 
	animationWorld = new MatrixBuffer;

	SetLocalPosition(500, 500);
	UpdateWorld();
	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();

}

Item::~Item()
{
	delete animation;
	delete animationTransform;
	delete animationWorld;
}

void Item::Update()
{
	animation->Update(0);
}

void Item::Render()
{
	RectCollider::Render();
	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(0);
}

void Item::SpawnItem(Vector2 pos)
{
	isActive = true;
	SetLocalPosition(pos);
	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Item::CollisionPlayer(Player* player)
{
	if (!IsRectCollision(player, nullptr)) return;
	isActive = false;
	PlayerGetItem(player);
	Audio::Get()->Play("ef_GetItem");
}

void Item::LoadAnimation()
{
	animation->LoadClip(path, "Idle.xml", true, 0.6f);
}

