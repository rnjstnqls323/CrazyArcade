#pragma once

class MonsterManager :public Singleton<MonsterManager>
{
	friend class Singleton;

private:
	const int STAR_POOL_SIZE = 25;

private:
	MonsterManager();
	~MonsterManager();

public:
	void Update();
	void Render();

	void AddNode(unordered_map<int, MonsterPos> pos);

	//여기서 주위 블럭 체크하는거 만들자. 
private:
	void ClearNode();
	template<typename T>
	void CreateMonsters(MonsterType key)
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
	unordered_map<MonsterType, vector<Monster*>> monsters; 
	unordered_map<MonsterType, vector<MonsterPos>> monsterPos;

};