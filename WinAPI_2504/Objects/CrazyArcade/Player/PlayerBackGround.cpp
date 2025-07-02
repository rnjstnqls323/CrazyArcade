#include "Framework.h"

PlayerBackGroundType PlayerBackGround::curType = PlayerBackGroundType::Basic;
PlayerBackGround::PlayerBackGround(Vector2 pos)
{
	SetLocalPosition(pos);
	UpdateWorld();
	CreateQuad();
}

PlayerBackGround::~PlayerBackGround()
{
	for (auto& quad : quads)
	{
		delete quad.second;
	}
	quads.clear();
}

void PlayerBackGround::Render()
{
	quads[curType]->Render();
}


wstring PlayerBackGround::GetBackGroundTypeToWString(PlayerBackGroundType type)
{
	switch (type)
	{
	case PlayerBackGroundType::Basic:
		return L"Basic";
	case PlayerBackGroundType::Clover:
		return L"Clover";
	case PlayerBackGroundType::Cute:
		return L"Cute";
	case PlayerBackGroundType::Dragon:
		return L"Dragon";
	case PlayerBackGroundType::Gold:
		return L"Gold";
	case PlayerBackGroundType::Green:
		return L"Green";
	case PlayerBackGroundType::Hopi:
		return L"Hopi";
	}
}

void PlayerBackGround::CreateQuad()
{
	wstring path = L"Resources/Textures/CrazyArcade_Player/BackGround/";
	for (int i = 0;i < (int)PlayerBackGroundType::Hopi +1 ;i++)
	{
		wstring name = ChangeTypeToWstring((PlayerBackGroundType)i);
		quads[(PlayerBackGroundType)i] = new Quad(path + name +L".png");

		quads[(PlayerBackGroundType)i]->SetParent(this);
		quads[(PlayerBackGroundType)i]->UpdateWorld();
	}
}

wstring PlayerBackGround::ChangeTypeToWstring(PlayerBackGroundType name)
{
	switch (name)
	{
	case PlayerBackGroundType::Basic:
		return L"Basic";
		break;
	case  PlayerBackGroundType::Clover:
		return L"Clover";
		break;
	case  PlayerBackGroundType::Cute:
		return L"Cute";
		break;
	case  PlayerBackGroundType::Dragon:
		return L"Dragon";
		break;
	case  PlayerBackGroundType::Gold:
		return L"Gold";
		break;
	case  PlayerBackGroundType::Green:
		return L"Green";
		break;
	case  PlayerBackGroundType::Hopi:
		return L"Hopi";
		break;

	}
}

