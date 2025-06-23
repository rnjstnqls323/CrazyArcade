#include "Framework.h"

Player::CharacterName Player::character = Player::Cappi;
Player::Player()
{
	CreateAnimation();
	LoadAnimation();
	animationTransform->SetLocalPosition(this->GetLocalPosition().x, this->GetLocalPosition().y + 17);
	animationTransform->UpdateWorld();
}

Player::~Player()
{
	DeleteAnimation();
}

void Player::Update()
{
	Move();

	animation[character]->Update(curStatus);

	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Player::Render()
{
	RectCollider::Render();
	if (curStatus == Die)//일케하면안될듯 재생안되고있으면 isdie트루로주자
		return;

	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation[character]->Render(curStatus);
}


string Player::CharacterNameToString(CharacterName name)
{
	switch (name)
	{
	case Player::Bazzi:
		return "Bazzi";
	case Player::Dao:
		return "Dao";
	case Player::Uni:
		return "Uni";
	case Player::Cappi:
		return "Cappi";
	case Player::Marid:
		return "Marid";
	case Player::Dizni:
		return "Dizni";
	}
}

void Player::LoadAnimation()
{
	string path = "Resources/Textures/CrazyArcade_Player/";


	for (int i = 0;i <= (int)Cappi;i++)
	{
		string file = CharacterNameToString((CharacterName)i)+"/";
		
		animation[(CharacterName)i]->LoadClip(path + file, "idle.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "up.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "down.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "left.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "right.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "trap.xml", true);
		animation[(CharacterName)i]->LoadClip(path + file, "live.xml", false);
		animation[(CharacterName)i]->LoadClip(path + file, "die.xml", false);
		
	}
	
}

void Player::CreateAnimation()
{
	for (int i = 0;i <= (int)Cappi;i++)
	{
		animation[(CharacterName)i] = new Animation;
	}
}

void Player::DeleteAnimation()
{
	for (int i = 0;i <= (int)Cappi;i++)
	{
		delete animation[(CharacterName)i];
	}
	animation.clear();
}
