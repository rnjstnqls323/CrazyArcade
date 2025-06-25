#include "Framework.h"

MonsterManager::MonsterManager()
{
	CreateMonsters<PinkStar>(MonsterType::PinkStar);
	CreateMonsters<PurpleStar>(MonsterType::PurpleStar);
	CreateMonster<TuttleKing>(MonsterType::TuttleKing);
}

MonsterManager::~MonsterManager()
{
	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
		{
			delete mon;
		}
		monster.second.clear();
	}
	monsters.clear();
	for (auto& monPos : monsterPos)
	{
		monPos.second.clear();
	}
	monsterPos.clear();
}

void MonsterManager::Update()
{
	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
		{
			if (!mon->IsActive())
				continue;
			MonsterCheckDie(mon);
			if (mon->GetMonsterStatus() != MonsterTrapMove)
				MonsterCollisionMonster(mon);
			mon->Update();
		}
	}
}

void MonsterManager::Render()
{
	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
		{
			if (!mon->IsActive())
				continue;
			mon->Render();
		}
	}
}

void MonsterManager::ResetManager()
{
	for (auto& monPos : monsterPos)
	{
		monPos.second.clear();
	}
	monsterPos.clear();

	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
			mon->ResetMonster();
	}
}

void MonsterManager::AddNode(TileMap* map,unordered_map<int, MonsterPos> pos)
{
	this->map = map;
	ClearNode();

	for (auto& position : pos)
	{
		MonsterPos mPos = position.second;
		if (mPos.endPos == Vector2(0, 0))
			mPos.endPos = mPos.startPos;
		if (mPos.type == MonsterType::PinkStar)
		{
			monsterPos[MonsterType::PinkStar].emplace_back(mPos);
		}
		else if (mPos.type == MonsterType::PurpleStar)
		{
			monsterPos[MonsterType::PurpleStar].emplace_back(mPos);
		}
	}

	vector<MonsterPos> origin = monsterPos[MonsterType::PurpleStar];

	for (const MonsterPos& pos : origin)
	{
		MonsterPos mPos = pos;
		swap(mPos.startPos, mPos.endPos);
		monsterPos[MonsterType::PurpleStar].push_back(mPos);
	}
}

void MonsterManager::MonsterSpawn()
{
	for (auto& monPos : monsterPos)
	{
		for (auto& mon : monPos.second)
		{
			if (mon.isLive)
				continue;
			SpawnMonster(mon);
			mon.isLive = true;
			//return; // test end remove
		}
	}
}

bool MonsterManager::MonsterCollisionPlayer(Player* player)
{
	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
		{
			if (!mon->IsActive())
				continue;
			Vector2 overlap;
			bool isCollision = mon->IsRectCollision(player, &overlap);
			if (mon->GetMonsterStatus() == MonsterTrap && isCollision)
			{
				mon->SetMonsterStatus(MonsterTrapMove);
				mon->SetTrap(true);
				mon->SetHitDir(overlap,player->GetLocalPosition());
				trapMoveMonster.insert(mon);
			}
			else if (isCollision && !mon->IsDeadOrTrap())
				player->Die();
		}
	}
	return false;
}


void MonsterManager::MonsterCollisionMonster(Monster* monster)
{
	for (Monster* mon : trapMoveMonster)
	{
		if (mon->IsRectCollision(monster, nullptr))
			monster->SetMonsterStatus(MonsterDie);
	}
}

void MonsterManager::MonsterCheckDie(Monster* mon)
{
	Index2 monIndex = map->GetTileIndex(mon);
	if (map->GetTileType(monIndex) == WaterTile && !mon->IsDeadOrTrap())
		mon->SetMonsterStatus(MonsterTrap);
	else if (mon->GetMonsterStatus() == MonsterTrapMove)
		if (map->GetTileType(monIndex) == BlockTile || map->GetTileType(monIndex) == CrushTile)
		{
			mon->SetMonsterStatus(MonsterTrapDie);
			if (mon->GetMonsterType() == MonsterType::PinkStar)
			{
				//같은 생성위치인거 찾아서 false로끄던지 아니면 새로 생성하고 끝내던지
			}
			trapMoveMonster.erase(mon);
		}
}

void MonsterManager::SpawnMonster(MonsterPos pos)
{
	for (Monster* monster : monsters[pos.type])
	{
		if (monster->IsActive())
			continue;
		monster->SetActive(true);
		monster->SetStartPos(pos.startPos);
		monster->SetEndPos(pos.endPos);
		monster->SetLocalPosition(pos.startPos);
		return;
	}
}

void MonsterManager::ClearNode()
{
	for (pair<const MonsterType, vector<MonsterPos>>& monPos : monsterPos)
	{
		monPos.second.clear();
	}
	monsterPos.clear();
}
