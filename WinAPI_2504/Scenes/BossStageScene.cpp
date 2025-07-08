#include "Framework.h"
#include "BossStageScene.h"

BossStageScene::BossStageScene()
{
	curStatus = Boss;
	CreatePlayerMap();
	audioKey = "bg_Stage3";
}

BossStageScene::~BossStageScene()
{
}

void BossStageScene::Start()
{
	PlayScene::Start();
	MonsterManager::Get()->SpawnTuttleKing();
}
void BossStageScene::End()
{
	PlayScene::End();
	if (Audio::Get()->IsPlaySound("bg_BossAttack"))
		Audio::Get()->Stop("bg_BossAttack");
}
void BossStageScene::CreatePlayerMap()
{
	map = new TileMap("Stage1.map");
	player = new Player();
}
