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
	if (isDead)
	{
		MonsterSpawn();
		isDead = false;
	}
	if (monsterPos[MonsterType::PurpleStar].size() == 0)
	{
		isDead = false; // 이거 지우고 씬 넘어가는거 구현하면됨
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
				mon->SetHitDir(overlap,player->GetLocalPosition());
				trapMoveMonster.insert(mon);
			}
			else if (isCollision && !mon->IsDeadOrTrap())
				player->Die();
		}
	}
	return false;
}

void MonsterManager::DeadMonster(Monster* monster)
{
	if (monster->GetMonsterType() == MonsterType::PinkStar)
	{
		for (MonsterPos& pos : monsterPos[MonsterType::PinkStar])
		{
			if (pos.startPos == monster->GetStartPos())
			{
				pos.isLive = false;
				isDead = true;
			}
		}
	}
	else if (monster->GetMonsterType() == MonsterType::PurpleStar)
	{
		auto& mon = monsterPos[MonsterType::PurpleStar];
		for (auto it = mon.begin(); it != mon.end(); ) {
			if (it->startPos == monster->GetStartPos()) {
				it = mon.erase(it); 
			}
			else {
				++it;
			}
		}
	}
}


void MonsterManager::MonsterCollisionMonster(Monster* monster)
{
	for (Monster* mon : trapMoveMonster)
	{
		if (mon->IsRectCollision(monster, nullptr))
			monster->SetMonsterStatus(MonsterDie);
	}
}

void MonsterManager::MonsterCheckDie(Monster* monster)
{
	Index2 monIndex = map->GetTileIndex(monster);
	if (map->GetTileType(monIndex) == WaterTile && !monster->IsDeadOrTrap())
		monster->SetMonsterStatus(MonsterTrap);
	else if (monster->GetMonsterStatus() == MonsterTrapMove)
		if (map->GetTileType(monIndex) == BlockTile || map->GetTileType(monIndex) == CrushTile)
		{
			monster->SetMonsterStatus(MonsterTrapDie);
			trapMoveMonster.erase(monster);
		}
}

void MonsterManager::SpawnMonster(MonsterPos pos)
{
	for (Monster* monster : monsters[pos.type])
	{
		if (monster->IsActive())
			continue;
		monster->SetActive(true);
		//monster->ResetMonster();
		monster->SetMonsterStatus(MonsterIdle);
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
