#pragma once

enum class MonsterType
{
	PinkStar, PurpleStar, TuttleKing
};
class MonsterManager :public Singleton<MonsterManager>
{
	friend class Singleton;

private:
	const int STAR_POOL = 25;

private:
	MonsterManager();
	~MonsterManager();

public:
	void Update();
	void Render();

	//여기서 주위 블럭 체크하는거 만들자. 
	
private:
	unordered_map<MonsterType, vector<Monster*>> monsters; //템플릿으로 받자

};