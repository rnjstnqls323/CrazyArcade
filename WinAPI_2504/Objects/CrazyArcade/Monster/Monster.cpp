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
	StatusUpdate();

	if(timer > SPAWN_TIME)
		Move();
	MonsterCrush();


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

bool Monster::MonsterCollisionPlayer(Player* player)
{
	Vector2 overlap;
	if (!IsRectCollision(player, &overlap) || curStatus == MonsterIdle) return false;
	
	if (curStatus == MonsterTrap)
	{
		SetMonsterStatus(MonsterTrapMove);
		SetHitDir(overlap, player->GetLocalPosition());
		MonsterManager::Get()->TrapMoveMonsterInsert(this);
		return false;
	}

	if (IsDeadOrTrap() || player->IsDieOrTrap()) return false;
	return true;
}

bool Monster::MonsterCollisionMonster(Monster* monster)
{
	if (curStatus == MonsterTrapMove) return false;
	if (IsRectCollision(monster, nullptr))
	{
		SetMonsterStatus(MonsterDie);
		return false;
	}
}

void Monster::ResetMonster()
{
	curStatus = MonsterIdle;
	forward = true;
	lerpT = 0.0f;
	isActive = false;
	hitDir = Vector2{ 0,0 };
	timer = 0.0f;
}

void Monster::SetHitDir(Vector2 overlap, Vector2 playerPos)
{
	Vector2 monsterPos = this->GetLocalPosition();

	float diffX = monsterPos.x - playerPos.x;
	float diffY = monsterPos.y - playerPos.y;

	if (overlap.x < overlap.y)
	{
		hitDir = (diffX > 0) ? Vector2(1, 0) : Vector2(-1, 0);
	}
	else
	{
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

void Monster::StatusUpdate()
{
	switch (curStatus)
	{
	case MonsterIdle:
		timer += DELTA;
		break;
	case MonsterTrap:
		timer += DELTA;
		break;
	case MonsterDie:
		Dead();
		break;
	case MonsterTrapDie:
		Dead();
		break;
	}
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

	LinearMove();
}

void Monster::LinearMove()
{
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

void Monster::Dead()
{
	if (animation->IsPlay(curStatus))
		return;
	isActive = false;
	MonsterManager::Get()->DeadMonster(this);
	ResetMonster();
}

void Monster::MonsterCrush()
{
	if (timer < CRUSH_TIME)return;

	timer = 0.0f;
	curStatus = MonsterTrapDie;
	animation->Play(MonsterTrapDie);
}


