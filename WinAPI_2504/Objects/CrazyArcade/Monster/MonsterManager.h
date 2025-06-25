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
	void Update();
	void Render();

	void ResetManager();

	void AddNode(TileMap* map, unordered_map<int, MonsterPos> pos);
	void MonsterSpawn();

	bool MonsterCollisionPlayer(Player* player);

	
private:
	void MonsterCollisionMonster(Monster* monster);
	void MonsterCheckDie(Monster* mon);

	void SpawnMonster(MonsterPos pos);
	void ClearNode();
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

	TileMap* map;
	unordered_map<MonsterType, vector<Monster*>> monsters; 
	unordered_map<MonsterType, vector<MonsterPos>> monsterPos;
	unordered_set<Monster*> trapMoveMonster;
};