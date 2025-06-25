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
public:
	Monster();
	Monster(Vector2 size);
	~Monster();

	virtual void Update();
	void Render();

	void SetStartPos(Vector2 pos) { startPos = pos; }
	void SetEndPos(Vector2 pos) { endPos = pos; }

	MonsterStatus GetMonsterStatus() { return curStatus; }
	void SetMonsterStatus(MonsterStatus status) { curStatus = status; }

	void ResetMonster();
	void SetTrap(bool isTrap) { this -> isTrap = isTrap; }
	void SetHitDir(Vector2 overlap,Vector2 playerPos);
	bool IsDeadOrTrap();

	virtual MonsterType GetMonsterType() { return MonsterType::TuttleKing; }
	//virtual bool IsPlayerHitTrapMonster(); 몬스터 관리도 걍 싱글톤에서할건디 굳이 여기서..?
protected:
	virtual void Move();
	void HitMove();

	virtual void LoadAnimation() = 0;

protected:
	int tag = -1;
	float speed = 1.0f; 
	bool forward=true;
	float lerpT = 0.0f;
	bool isTrap = false;

	Vector2 startPos;
	Vector2 endPos;
	Vector2 hitDir;

	MonsterStatus curStatus = MonsterIdle;
	Animation* animation;
	Transform* animationTransform;
	MatrixBuffer* worldBuffer;

};