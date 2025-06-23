#include "Framework.h"

Character::Character():RectCollider(Vector2(35,30))
{
	animation = new Animation;
	//LoadAnimation(); 이거 상속받는 애들에서 하자

	animationTransform = new Transform;
	animationTransform->SetParent(this);

}

Character::~Character()
{
	delete animation;
	delete animationTransform;
}


void Character::Move()
{
	Vector2 curPos = GetLocalPosition();
	isKeyPress = false;

	if (Input::Get()->IsKeyPress(VK_UP))
	{
		isKeyPress = true;
		Translate(Vector2::Up() * speed * DELTA);
		curStatus = MoveUp;
	}
	else if (Input::Get()->IsKeyPress(VK_DOWN))
	{
		isKeyPress = true;
		Translate(Vector2::Down() * speed * DELTA);
		curStatus = MoveDown;
	}
	else if (Input::Get()->IsKeyPress(VK_LEFT))
	{
		isKeyPress = true;
		Translate(Vector2::Left() * speed * DELTA);
		curStatus = MoveLeft;
	}
	else if (Input::Get()->IsKeyPress(VK_RIGHT))
	{
		isKeyPress = true;
		Translate(Vector2::Right() * speed * DELTA);
		curStatus = MoveRight;
	}

}
