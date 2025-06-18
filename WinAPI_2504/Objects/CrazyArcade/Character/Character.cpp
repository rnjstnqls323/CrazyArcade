#include "Framework.h"

Character::Character():RectCollider(Vector2(35,30))
{
	animation = new CharacterAnimation;
	LoadAnimation();

	animationTransform = new Transform;
	animationTransform->SetParent(this);
	animationTransform->SetLocalPosition(this->GetLocalPosition().x , this->GetLocalPosition().y+17);
	animationTransform->UpdateWorld();
}

Character::~Character()
{
	delete animation;
	delete animationTransform;

}

void Character::Update()
{
	Move();

	animation->Update(curStatus);

	UpdateWorld();
	animationTransform->UpdateWorld();

}

void Character::Render()
{
	RectCollider::Render();
	if (curStatus == Die)//일케하면안될듯 재생안되고있으면 isdie트루로주자
		return;
	
	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(curStatus);

}

void Character::LoadAnimation()
{
	string path = "Resources/Textures/CrazyArcade_Player/Bazzi/";

	animation->LoadClip(path, "bazzi_idle.xml", true);
	animation->LoadClip(path, "bazzi_up.xml", true);
	animation->LoadClip(path, "bazzi_down.xml", true);
	animation->LoadClip(path, "bazzi_left.xml", true);
	animation->LoadClip(path, "bazzi_right.xml", true);
	animation->LoadClip(path, "bazzi_trap.xml", true);
	animation->LoadClip(path, "bazzi_live.xml", false);
	animation->LoadClip(path, "bazzi_die.xml", false);
}

void Character::Move()
{
	Vector2 curPos = GetLocalPosition();
	isKeyPress = false;

	if (Input::Get()->IsKeyPress(VK_UP))
	{
		Translate(Vector2::Up() * speed * DELTA);
		curStatus = MoveUp;
	}
	else if (Input::Get()->IsKeyPress(VK_DOWN))
	{
		Translate(Vector2::Down() * speed * DELTA);
		curStatus = MoveDown;
	}
	else if (Input::Get()->IsKeyPress(VK_LEFT))
	{
		Translate(Vector2::Left() * speed * DELTA);
		curStatus = MoveLeft;
	}
	else if (Input::Get()->IsKeyPress(VK_RIGHT))
	{
		Translate(Vector2::Right() * speed * DELTA);
		curStatus = MoveRight;
	}

}
