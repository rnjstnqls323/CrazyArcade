#include "Framework.h"

PurpleStar::PurpleStar()
{
	LoadAnimation();
}

PurpleStar::~PurpleStar()
{
}

void PurpleStar::LoadAnimation()
{
	string path = "Resources/Textures/CrazyArcade_Monster/PurpleStar/";
	animation->LoadClip(path, "idle.xml", false, 0.5f);
	animation->LoadClip(path, "up.xml", true, 0.5f);
	animation->LoadClip(path, "down.xml", true, 0.5f);
	animation->LoadClip(path, "left.xml", true, 0.5f);
	animation->LoadClip(path, "right.xml", true, 0.5f);
	animation->LoadClip(path, "die.xml", false, 0.8f);
	animation->LoadClip(path, "trap.xml", false, 0.6f);
	animation->LoadClip(path, "trapmove.xml", true, 0.7f);
	animation->LoadClip(path, "trapdie.xml", false, 0.7f);

}
