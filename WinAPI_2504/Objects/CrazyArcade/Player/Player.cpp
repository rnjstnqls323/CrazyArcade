#include "Framework.h"

Player::CharacterName Player::character = Player::Marid;
Player::Player():RectCollider(Vector2(35, 30))
{
	CreateAnimation();
	LoadAnimation();
	animationTransform = new Transform;
	animationTransform->SetParent(this);
	animationTransform->SetLocalPosition(this->GetLocalPosition().x, this->GetLocalPosition().y + 17);
	animationTransform->UpdateWorld();
}

Player::~Player()
{
	DeleteAnimation();
	delete animationTransform;
}

void Player::Update()
{
	StatusUpdate();
	IdleChange();
	animation[character]->Update(curStatus);

	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Player::Render()
{
	RectCollider::Render();
	//if (curStatus == CharacterDie)//일케하면안될듯 재생안되고있으면 isdie트루로주자
	//	return;

	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation[character]->Render(curStatus);
}

void Player::Die()
{
	if (curStatus == CharacterDie) return;
	curStatus = CharacterDie;
	animation[character]->Play(curStatus);
}

void Player::Trap()
{
	curStatus = BubbleTrapped;
	animation[character]->Play(curStatus);
	isTrap = true;
}

bool Player::IsDieOrTrap()
{
	if (curStatus == CharacterDie || curStatus == BubbleTrapped)
		return true;
	return false;
}


void Player::Move()
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

string Player::CharacterNameToString(CharacterName name)
{
	switch (name)
	{
	case Player::Bazzi:
		return "Bazzi";
	case Player::Dao:
		return "Dao";
	case Player::Cappi:
		return "Cappi";
	case Player::Marid:
		return "Marid";
	case Player::Hook:
		return "Hook";
	}
}

void Player::LoadAnimation()
{
	string path = "Resources/Textures/CrazyArcade_Player/";


	for (int i = 0;i < (int)EndCharacter;i++)
	{
		string file = CharacterNameToString((CharacterName)i)+"/";
		
		animation[(CharacterName)i]->LoadClip(path + file, "upidle.xml", false);
		animation[(CharacterName)i]->LoadClip(path + file, "downidle.xml", false);
		animation[(CharacterName)i]->LoadClip(path + file, "leftidle.xml", false);
		animation[(CharacterName)i]->LoadClip(path + file, "rightidle.xml", false);
		animation[(CharacterName)i]->LoadClip(path + file, "up.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "down.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "left.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "right.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "trap.xml", false,0.7f);
		animation[(CharacterName)i]->LoadClip(path + file, "die.xml", false, 0.7f);
		animation[(CharacterName)i]->LoadClip(path + file, "live.xml", false, 0.4f);
		
	}
	
}

void Player::CreateAnimation()
{
	for (int i = 0;i < (int)EndCharacter;i++)
	{
		animation[(CharacterName)i] = new Animation;
	}
}

void Player::DeleteAnimation()
{
	for (int i = 0;i < (int)EndCharacter;i++)
	{
		delete animation[(CharacterName)i];
	}
	animation.clear();
}
void Player::StatusUpdate()
{
	switch (curStatus)
	{
	case BubbleTrapped:
		TrapPlayer();
		break;
	case CharacterDie:
		Move(); // 바꿔줘야됨
		break;
	case CharacterLive:
		if (!animation[character]->IsPlay(curStatus))
			curStatus = DownIdle;
		break;
	default:
		Move();
		break;
	}
}

void Player::TrapPlayer()
{
	timer += DELTA;
	if (Input::Get()->IsKeyPress(VK_LCONTROL))
	{
		curStatus = CharacterLive;
		animation[character]->Play(curStatus);
		timer = 0.0f;
		isTrap = false;
	}
	else if (timer > DEAD_TIME)
	{
		curStatus = CharacterDie;
		animation[character]->Play(curStatus);
	}
}

void Player::IdleChange()
{
	if (isKeyPress) return;
	switch (curStatus)
	{
	case MoveUp:
		curStatus = UpIdle;
		break;
	case MoveDown:
		curStatus = DownIdle;
		break;
	case MoveLeft:
		curStatus = LeftIdle;
		break;
	case MoveRight:
		curStatus = RightIdle;
		break;
	}
}
