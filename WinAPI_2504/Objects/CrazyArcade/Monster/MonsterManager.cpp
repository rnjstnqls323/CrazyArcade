#include "Framework.h"

MonsterManager::MonsterManager()
{
	monsters[MonsterType::PinkStar].resize(STAR_POOL_SIZE);
	monsters[MonsterType::PurpleStar].resize(STAR_POOL_SIZE);
	monsters[MonsterType::TuttleKing].resize(STAR_POOL_SIZE);

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
}

void MonsterManager::Update()
{
	for (auto& monster : monsters)
	{
		for (Monster* mon : monster.second)
		{
			if (!mon->IsActive())
				continue;
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

void MonsterManager::AddNode(unordered_map<int, MonsterPos> pos)
{
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
}

void MonsterManager::ClearNode()
{
	for (pair<const MonsterType, vector<MonsterPos>>& monPos : monsterPos)
	{
		monPos.second.clear();
	}
	monsterPos.clear();
}
