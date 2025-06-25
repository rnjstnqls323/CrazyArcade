#pragma once

enum MonsterStatus
{
	MonsterIdle, MonsterUp, MonsterDown, MonsterLeft, MonsterRight,MonsterDie, MonsterTrap, 
	MonsterTrapMove, MonsterTrapDie
};
enum class MonsterType
{
	PinkStar, PurpleStar, TuttleKing
};
struct MonsterPos
{
	Vector2 startPos;
	Vector2 endPos;
	MonsterType type;
	bool isLive = false;
};

class Monster :public RectCollider 
{
	//죽으면 애니 다 끝나고 die처리해야됨 핑크는 die다시 스폰해야됨
private:
	const int HIT_SPEED = 500;
	const float SPAWN_TIME = 1.0f;
	const float CRUSH_TIME = 6.0f;
public:
	Monster();
	Monster(Vector2 size);
	~Monster();

	virtual void Update();
	void Render();
	
	Vector2 GetStartPos() { return startPos; }
	void SetStartPos(Vector2 pos) { startPos = pos; }
	void SetEndPos(Vector2 pos) { endPos = pos; }

	MonsterStatus GetMonsterStatus() { return curStatus; }
	void SetMonsterStatus(MonsterStatus status) 
	{ 
		curStatus = status; 
		animation->Play(curStatus);
	}

	void ResetMonster();
	void SetHitDir(Vector2 overlap,Vector2 playerPos);
	bool IsDeadOrTrap();

	virtual MonsterType GetMonsterType() { return MonsterType::TuttleKing; }
	
protected:
	void StatusUpdate();
	virtual void Move();
	void LinearMove();
	void HitMove();
	void Dead();
	void MonsterCrush();

	virtual void LoadAnimation() = 0;

protected:
	double timer = 0.0f;
	int tag = -1;
	float speed = 1.0f; 
	bool forward=true;
	float lerpT = 0.0f;

	Vector2 startPos;
	Vector2 endPos;
	Vector2 hitDir;

	MonsterStatus curStatus = MonsterIdle;
	Animation* animation;
	Transform* animationTransform;
	MatrixBuffer* worldBuffer;

};