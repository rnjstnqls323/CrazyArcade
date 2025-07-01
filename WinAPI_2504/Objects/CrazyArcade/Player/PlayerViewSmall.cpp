#include "Framework.h"

PlayerViewSmall::PlayerViewSmall()
{
	SetLocalPosition(Vector2(1065, 715));
	UpdateWorld();
	CreateQuads();
}

PlayerViewSmall::~PlayerViewSmall()
{
	for (auto& quad : quads)
	{
		delete quad.second;
	}
	quads.clear();
}

void PlayerViewSmall::Render()
{
	quads[Player::GetCharacter()]->Render();
}

void PlayerViewSmall::CreateQuads()
{
	wstring path = L"Resources/Textures/CrazyArcade_UI/Play/";
	for (int i = 0;i < (int)CharacterName::EndCharacter;i++)
	{
		wstring name = ChangeCharacterNameToWstirng((CharacterName)i);
		quads[(CharacterName)i] = new Quad(path + name + L".png");

		quads[(CharacterName)i]->SetLocalScale(1.5, 1.5);
		quads[(CharacterName)i]->SetParent(this);
		quads[(CharacterName)i]->UpdateWorld();
	}
}

wstring PlayerViewSmall::ChangeCharacterNameToWstirng(CharacterName name)
{
	switch (name)
	{
	case CharacterName::Bazzi:
		return L"Bazzi";
		break;
	case CharacterName::Cappi:
		return L"Cappi";
		break;
	case CharacterName::Dao:
		return L"Dao";
		break;
	case CharacterName::Hook:
		return L"Hook";
		break;
	case CharacterName::Marid:
		return L"Marid";
		break;
	}
}
