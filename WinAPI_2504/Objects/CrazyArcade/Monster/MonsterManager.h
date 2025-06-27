#pragma once

class MonsterManager :public Singleton<MonsterManager>
{
	friend class Singleton;

private:
	const int STAR_POOL_SIZE = 30;

private:
	MonsterManager();
	~MonsterManager();

public:
	void Update(Player* player);
	void Render();

	void ResetManager();

	void AddMonsterPos(TileMap* map, unordered_map<int, MonsterPos> pos);
	void MonsterSpawn();



	void DeadMonster( Monster* monster);
	
	void SpawnTuttleKing();

	void TrapMoveMonsterInsert(Monster* monster)
	{
		trapMoveMonster.insert(monster);
	}

private:
	void BlockBubbleMonster(Monster* monster);
	void MonsterCollisionMonster(Monster* monster);
	void MonsterCheckDie(Monster* monster);

	void MonsterCollisionPlayer(Monster* monster, Player* player);

	void SpawnMonster(MonsterPos pos);
	void ClearMonsterPos();
	void GeneratePathTuttleKing(Monster* monster, Player* player);
	template<typename T>
	void CreateMonsters(MonsterType key) 
	{
		for (int i = 0; i < STAR_POOL_SIZE; i++)
		{
			T* monster = new T;
			monster->SetActive(false);
			monsters[key].push_back(monster);
		}
	}
	template<typename T>
	void CreateMonster(MonsterType key)
	{
		T* monster = new T;
		monster->SetActive(false);
		monsters[key].push_back(monster);
	}
	

private:
	bool isDead = false;

	
	AStar* astar;
	TileMap* map;
	unordered_map<MonsterType, vector<Monster*>> monsters; 
	unordered_map<MonsterType, vector<MonsterPos>> monsterPos;
	unordered_set<Monster*> trapMoveMonster;
	unordered_set<Monster*> eraseMonster;
};