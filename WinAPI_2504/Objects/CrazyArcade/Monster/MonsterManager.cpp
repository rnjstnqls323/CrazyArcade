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
	delete astar;
}

void MonsterManager::Update(Player* player)
{
	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
		{
			if (!mon->IsActive())
				continue;
			MonsterCheckDie(mon);
			MonsterCollisionPlayer(mon, player);
			MonsterCollisionMonster(mon);
			BlockBubbleMonster(mon);
			if (mon->GetMonsterType() == MonsterType::TuttleKing)
				GeneratePathTuttleKing(mon, player);
			mon->Update();
		}
	}
	CheckMonsterDie();
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
	//if (astar != nullptr)
	//	astar->Render();
}
void MonsterManager::AddMonsterPos(TileMap* map, unordered_map<int, MonsterPos> pos)
{
	this->map = map;
	if(astar == nullptr)
		astar = new AStar(map);
	ClearMonsterPos();

	for (auto& position : pos)
	{
		MonsterPos mPos = position.second;
		if (mPos.endPos == Vector2(0, 0))
			mPos.endPos = mPos.startPos;
		if (mPos.startPos == Vector2(0, 0))
			mPos.startPos = mPos.endPos;
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

void MonsterManager::MonsterCollisionPlayer(Monster* monster, Player* player)
{
	if (monster->MonsterCollisionPlayer(player))
		player->Die();
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

void MonsterManager::SpawnTuttleKing()
{
	isKing = true;
	TuttleKing* king = (TuttleKing*)monsters[MonsterType::TuttleKing][0];
	king->SetActive(true);
	king->SetKingStatus(KingIdle);
	king->SetLocalPosition(1000, 500);
}


void MonsterManager::Reset()
{
	isKing = false;
	isDead = false;
	for (auto& monPos : monsterPos)
	{
		monPos.second.clear();
	}
	monsterPos.clear();

	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
			mon->Reset();
	}
	eraseMonster.clear();
	trapMoveMonster.clear();

}

void MonsterManager::CheckMonsterDie()
{
	if (isDead)
	{
		MonsterSpawn();
		isDead = false;
	}

	if (monsterPos[MonsterType::PurpleStar].size() == 0 && !isKing)
	{
		EventManager::Get()->ExcuteEvent("EndStage", nullptr);
		Audio::Get()->Play("ef_Win");
		UIManager::Get()->AddShowPanel(PanelType::WinPanel);
	}
	else if (isKing && monsters[MonsterType::TuttleKing][0]->GetMonsterStatus() == KingDie)
	{
		EventManager::Get()->ExcuteEvent("EndStage", nullptr);
		Audio::Get()->Play("ef_Win");
		UIManager::Get()->AddShowPanel(PanelType::WinPanel);
	}
}

void MonsterManager::BlockBubbleMonster(Monster* monster)
{
	if (monster->GetMonsterType() == MonsterType::TuttleKing) return;
	Index2 monIndex = map->GetTileIndex(monster);
	if (map->GetTileType(monIndex) == BubbleTile)
		monster->SetIsCollision(true);
}

void MonsterManager::MonsterCollisionMonster(Monster* monster)
{
	eraseMonster.clear();
	for (Monster* mon : trapMoveMonster)
	{
		if (monster->MonsterCollisionMonster(mon))
			eraseMonster.insert(mon);
	}
	for (Monster* mon : eraseMonster)
	{
		trapMoveMonster.erase(mon);
	}
}

void MonsterManager::MonsterCheckDie(Monster* monster)
{
	Index2 monIndex = map->GetTileIndex(monster);
	if (monster->GetMonsterType() == MonsterType::TuttleKing)
	{
		TuttleKing* king = (TuttleKing*)monster;
		vector<Tile*> tiles = map->GetAroundEightTile(monIndex);
		if (king->GetKingStatus() == KingTrap || king->GetKingStatus() == KingDie) return;
		for (Tile* tile : tiles)
		{
			if (tile->GetTileType() == WaterTile && king->GetDamageTag() < tile->GetTileTag())
			{
				king->SetDamageTag(tile->GetTileTag());
				king->Damage();
			}
			if (tile->GetTileType() == BubbleTile)
			{
				BubbleManager::Get()->BombBubble(tile->GetTileIndex());
			}
		}
	}

	else
	{
		if (map->GetTileType(monIndex) == WaterTile && !monster->IsDeadOrTrap())
			monster->SetMonsterStatus(MonsterTrap);
		else if (monster->GetMonsterStatus() == MonsterTrapMove)
			if (map->GetTileType(monIndex) == BlockTile || map->GetTileType(monIndex) == CrushTile)
			{
				monster->SetMonsterStatus(MonsterTrapDie);
				trapMoveMonster.erase(monster);
			}
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

void MonsterManager::ClearMonsterPos()
{
	for (pair<const MonsterType, vector<MonsterPos>>& monPos : monsterPos)
	{
		monPos.second.clear();
	}
	monsterPos.clear();
}

void MonsterManager::GeneratePathTuttleKing(Monster* monster, Player* player)
{
	if (astar == nullptr) return;
	TuttleKing* king = (TuttleKing*)monster;
	if (king->GetKingStatus() == KingAttack)
	{
		int start = astar->FindCloseNode(king->GetLocalPosition());
		int end = astar->FindCloseNode(player->GetLocalPosition());
		king->SetPath(astar->GetPath(start, end));
	}
	
	else if(king->IsPathEmpty())
	{
		if (astar == nullptr)
			return;
		int start = astar->FindCloseNode(king->GetLocalPosition());
		int end = astar->FindRandomEndNode();
		king->SetPath(astar->GetPath(start, end));
	}
}
