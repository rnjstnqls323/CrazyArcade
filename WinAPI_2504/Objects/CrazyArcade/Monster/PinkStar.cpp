#include "Framework.h"

PinkStar::PinkStar()
{
	LoadAnimation();
	speed = 0.5f;
}

PinkStar::~PinkStar()
{
}

void PinkStar::LoadAnimation()
{
	string path = "Resources/Textures/CrazyArcade_Monster/PinkStar/";
	animation->LoadClip(path, "idle.xml", false,0.5f);
	animation->LoadClip(path, "up.xml", true, 0.5f);
	animation->LoadClip(path, "down.xml", true,0.5f);
	animation->LoadClip(path, "left.xml", true, 0.5f);
	animation->LoadClip(path, "right.xml", true, 0.5f);
	animation->LoadClip(path, "die.xml", false, 0.8f);
	animation->LoadClip(path, "trap.xml", false,0.6f);
	animation->LoadClip(path, "trapmove.xml", true,0.7f);
	animation->LoadClip(path, "trapdie.xml", false, 0.7f);

}

