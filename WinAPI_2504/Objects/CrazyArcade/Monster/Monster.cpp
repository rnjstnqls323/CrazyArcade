#include "Framework.h"

Monster::Monster():RectCollider(Vector2(35,35))
{
	animation = new Animation;
	animationTransform = new Transform;
	worldBuffer = new MatrixBuffer;

	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();
}

Monster::Monster(Vector2 size):RectCollider(size)
{
	animation = new Animation;
	animationTransform = new Transform;
	worldBuffer = new MatrixBuffer;

	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();
}

Monster::~Monster()
{
	delete animation;
	delete animationTransform;
	delete worldBuffer;

}

void Monster::Update()
{
	
	Move();

	animation->Update(curStatus);

	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Monster::Render()
{
	RectCollider::Render();
	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(curStatus);
}

void Monster::ResetMonster()
{
	curStatus = MonsterIdle;
	forward = true;
	lerpT = 0.0f;
	isActive = false;
	isTrap = false;
	hitDir = Vector2{ 0,0 };
}

void Monster::SetHitDir(Vector2 overlap, Vector2 playerPos)
{
	Vector2 monsterPos = this->GetLocalPosition();

	float diffX = monsterPos.x - playerPos.x;
	float diffY = monsterPos.y - playerPos.y;

	// 겹침 깊이 중 더 작은 축으로 튕길 방향 결정
	if (overlap.x < overlap.y)
	{
		// 좌우 중 하나로 튕기기
		hitDir = (diffX > 0) ? Vector2(1, 0) : Vector2(-1, 0);
	}
	else
	{
		// 상하 중 하나로 튕기기
		hitDir = (diffY > 0) ? Vector2(0, 1) : Vector2(0, -1);
	}
}

bool Monster::IsDeadOrTrap()
{
	if (curStatus == MonsterTrap || curStatus == MonsterTrapDie || curStatus == MonsterTrapMove
		|| curStatus == MonsterDie)
		return true;
	return false;
}

void Monster::Move()
{
	if (curStatus == MonsterDie || curStatus == MonsterTrapDie || curStatus == MonsterTrap)
		return;

	if (curStatus == MonsterTrapMove)
	{
		HitMove();
		return;
	}

	//endnode까지갔다가~ start위치바꾸고 오고 이렇게  선형보간법 사용하자
	Vector2 prePos = GetLocalPosition();
	float speedDelta = speed * DELTA;
	if (forward)
		lerpT += speedDelta;
	else
		lerpT -= speedDelta;

	if (lerpT >= 1.0f)
	{
		lerpT = 1.0f;
		forward = false;
	}
	else if (lerpT <= 0.0f)
	{
		lerpT = 0.0f;
		forward = true;
	}
	
	SetLocalPosition(Vector2::Lerp(startPos, endPos, lerpT));

	Vector2 moveDir = GetLocalPosition() - prePos;

	// 방향에 따라 상태 설정
	if (abs(moveDir.x) > abs(moveDir.y))
	{
		curStatus = (moveDir.x > 0) ? MonsterRight : MonsterLeft;
	}
	else
	{
		curStatus = (moveDir.y > 0) ? MonsterUp : MonsterDown;
	}
}

void Monster::HitMove()
{
	Translate(hitDir * HIT_SPEED * DELTA);
}


