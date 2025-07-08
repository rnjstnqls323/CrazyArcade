#include "Framework.h"
#include "Stage1Scene.h"

Stage1Scene::Stage1Scene()
{
	curStatus = Stage1;
	CreatePlayerMap();
	audioKey = "bg_Stage1";
}

Stage1Scene::~Stage1Scene()
{
}

void Stage1Scene::Start()
{
	PlayScene::Start();

	if (Player::GetCharacter() == CharacterName::Hook)
	{
		int num = rand() % (int)CharacterName::EndCharacter;
		Player::SetCharacter((CharacterName)num);
	}
}
void Stage1Scene::CreatePlayerMap()
{
	map = new TileMap("Stage1.map");
	player = new Player();
}
