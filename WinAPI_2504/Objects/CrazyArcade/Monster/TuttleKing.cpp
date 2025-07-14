#include "Framework.h"

TuttleKing::TuttleKing():Monster(Vector2(150,150))
{
	LoadAnimation();

	curStatus = MonsterDown;
	healthPointBar = new HealthPointBar(healthPoint);
	healthPointBar->SetParent(this);
	Vector2 pos = this->GetLocalPosition();
	healthPointBar->SetLocalPosition(pos.x, pos.y + 100);
	healthPointBar->UpdateWorld();
}

TuttleKing::~TuttleKing()
{
	delete healthPointBar;
}

void TuttleKing::Update()
{
	isAttack = false;
	AttackTime();
	StatusUpdate();

	animation->Update(kingStatus);
	UpdateWorld();
	animationTransform->UpdateWorld();
	healthPointBar->Update();

	if (kingStatus != KingAngry && kingStatus != KingAttack && Audio::Get()->IsPlaySound("bg_BossAttack"))
		Audio::Get()->Stop("bg_BossAttack");
}

void TuttleKing::Render()
{
	RectCollider::Render();
	worldBuffer->Set(animationTransform->GetWorld());
	worldBuffer->SetVS(0);
	animation->Render(kingStatus);
	healthPointBar->Render();
}

bool TuttleKing::MonsterCollisionPlayer(Player* player)
{
	Vector2 overlap;
	if (!IsRectCollision(player, &overlap) || kingStatus == KingIdle) return false;
	if (kingStatus == KingTrap)
	{
		SetKingStatus(KingDie);
		return false;
	}
	if (kingStatus == KingDie || player->IsDieOrTrap())
		return false;
	return true;
}

bool TuttleKing::MonsterCollisionMonster(Monster* monster)
{
	if (kingStatus == KingTrap || kingStatus == KingDie) return false;
	if (!monster || !IsRectCollision(monster, nullptr)) return false;
	Damage();
	monster->SetMonsterStatus(MonsterTrapDie);
	return true;
}


void TuttleKing::Damage()
{
	healthPoint -= DAMAGE;
	healthPointBar->SetLength(healthPoint);
	kingStatus = KingDamage;
	animation->Play(KingDamage);
}

void TuttleKing::Reset()
{
	curStatus = MonsterIdle;
	forward = true;
	lerpT = 0.0f;
	isActive = false;
	hitDir = Vector2{ 0,0 };
	timer = 0.0f;
	isCollision = false; //여기수정해야됨
	isDie = false;
	healthPoint = MAX_HEALTHPOINT;
	healthPointBar->SetLength(healthPoint);
}

void TuttleKing::Move()
{
	if (path.empty())
		return;

	Vector2 destPos = path.back();

	velocity = destPos - localPosition;

	if (velocity.Magnitude() < 1.0f)
	{
		path.pop_back();
	}
	else
	{
		velocity.Normalize();
	}

	if (kingStatus == KingAttack)
	{
		Translate(velocity * speed * DELTA);
		return;
	}

	const float threshold = 0.9f; // 1.0에 가까울수록 정방향에 가까움 + gpt도움 내적이용하는 방법

	if (velocity.Dot(velocity, Vector2::Up()) > threshold)
	{
		kingStatus = KingUp;
	}
	else if (velocity.Dot(velocity, Vector2::Down()) > threshold)
	{
		kingStatus = KingDown;
	}
	else if (velocity.Dot(velocity, Vector2::Left()) > threshold)
	{
		kingStatus = KingLeft;
	}
	else if (velocity.Dot(velocity, Vector2::Right()) > threshold)
	{
		kingStatus = KingRight;
	}

	Translate(velocity * speed * DELTA);
}

void TuttleKing::StatusUpdate()
{
	switch (kingStatus)
	{
	case KingUp:
	case KingDown:
	case KingLeft:
	case KingRight:
	case KingIdle:
		speed = MOVE_SPEED;
		Move();
		break;
	case KingAttack:
		speed = ATTACK_SPEED;
		isAttack = true;
		Move();
		break;
	case KingDamage:
		if (!animation->IsPlay(KingDamage) && healthPoint <= 0)
			kingStatus = KingTrap;
		else if (!animation->IsPlay(KingDamage))
			kingStatus = KingIdle;
		break;
	case KingAngry:
		if (!animation->IsPlay(KingAngry))
		{
			kingStatus = KingAttack;
		}
		break;
	case KingDie:
		if (!animation->IsPlay(KingDie) && !isDie)
		{
			curStatus = MonsterDie;
			isDie = true;
		}
		break;
	case KingTrap:
		TrapDeadTime();
		break;
	}
}

void TuttleKing::AttackTime()
{
	if (kingStatus == KingDie || kingStatus == KingTrap) return;

	timer += DELTA;

	if (timer >= ATTACK_TIME && !isAttack)
	{
		isAttack = true;
		Audio::Get()->Play("bg_BossAttack");
		kingStatus = KingAngry;
		timer = 0.0f;  // 다시 타이머 리셋
	}
	else if (isAttack && timer >= MOVE_TIME)
	{
		isAttack = false;
		kingStatus = KingIdle;
		timer = 0.0f;
		Audio::Get()->Stop("bg_BossAttack");
	}
	
}

void TuttleKing::TrapDeadTime()
{
	trapTimer += DELTA;
	if (trapTimer >= TRAP_TIME)
	{
		kingStatus = KingDie;
	}
}

void TuttleKing::LoadAnimation()
{

	string path = "Resources/Textures/CrazyArcade_Monster/TuttleKing/";
	animation->LoadClip(path, "idle.xml", false);
	animation->LoadClip(path, "attack.xml", true, 0.7f);
	animation->LoadClip(path, "damage.xml", false, 0.5f);
	animation->LoadClip(path, "angry.xml", false);
	animation->LoadClip(path, "die.xml", false, 0.5f);
	animation->LoadClip(path, "up.xml", true);
	animation->LoadClip(path, "down.xml", true, 0.3f);
	animation->LoadClip(path, "left.xml", true, 0.3f);
	animation->LoadClip(path, "right.xml", true, 0.3);
	animation->LoadClip(path, "trap.xml", false, 0.6f);
}
