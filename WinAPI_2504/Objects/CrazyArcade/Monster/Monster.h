#pragma once

enum MonsterStatus
{
	MonsterIdle, MonsterUp, MonsterDown, MonsterLeft, MonsterRight,MonsterDie, MonsterTrap, 
	MonsterTrapMove, MonsterTrapDie
};
class Monster :public RectCollider
{
public:
	Monster();
	Monster(Vector2 size);
	~Monster();

	virtual void Update();
	void Render();

	void SetStartPos(Vector2 pos) { startPos = pos; }
	void SetEndPos(Vector2 pos) { endPos = pos; }

	//virtual bool IsPlayerHitTrapMonster(); ¸ó½ºÅÍ °ü¸®µµ °Á ½Ì±ÛÅæ¿¡¼­ÇÒ°Çµð ±»ÀÌ ¿©±â¼­..?
protected:
	virtual void Move();

	virtual void LoadAnimation() = 0;

protected:
	int tag = -1;
	float speed = 100.0f; 

	Vector2 startPos;
	Vector2 endPos;

	Quad* test;
	MonsterStatus curStatus = MonsterIdle;
	Animation* animation;
	Transform* animationTransform;
	MatrixBuffer* worldBuffer;

};