#include "Framework.h"

TuttleKing::TuttleKing():Monster(Vector2(150,150))
{
	LoadAnimation();
}

TuttleKing::~TuttleKing()
{
}

void TuttleKing::Update()
{
	Move();

	animation->Update(kingStatus);

	UpdateWorld();
	animationTransform->UpdateWorld();
}

void TuttleKing::Render()
{
	RectCollider::Render();
	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(kingStatus);
}

void TuttleKing::LoadAnimation()
{

	string path = "Resources/Textures/CrazyArcade_Monster/TuttleKing/";
	animation->LoadClip(path, "idle.xml", false);
	animation->LoadClip(path, "attack.xml", true, 0.7f);
	animation->LoadClip(path, "damage.xml", false);
	animation->LoadClip(path, "angry.xml", false);
	animation->LoadClip(path, "die.xml", false, 0.5f);
	animation->LoadClip(path, "up.xml", true);
	animation->LoadClip(path, "down.xml", true, 0.3f);
	animation->LoadClip(path, "left.xml", true, 0.3f);
	animation->LoadClip(path, "right.xml", true, 0.3);
	animation->LoadClip(path, "trap.xml", false, 0.6f);
}
