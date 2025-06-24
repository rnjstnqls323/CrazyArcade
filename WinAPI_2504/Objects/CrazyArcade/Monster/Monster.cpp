#include "Framework.h"

Monster::Monster():RectCollider(Vector2(35,35))
{
	animation = new Animation;
	animationTransform = new Transform;
	worldBuffer = new MatrixBuffer;

	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();
}

Monster::Monster(Vector2 size):RectCollider(size)
{
	animation = new Animation;
	animationTransform = new Transform;
	worldBuffer = new MatrixBuffer;

	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();
}

Monster::~Monster()
{
	delete animation;
	delete animationTransform;
	delete worldBuffer;

}

void Monster::Update()
{
	Move();

	animation->Update(curStatus);

	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Monster::Render()
{
	RectCollider::Render();
	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(curStatus);
}

void Monster::Move()
{
	//endnode까지갔다가~ start위치바꾸고 오고 이렇게
}


