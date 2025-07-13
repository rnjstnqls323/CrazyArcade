#pragma once

enum KingStatus
{
	KingIdle, KingAttack, KingDamage, KingAngry, KingDie,
	KingUp, KingDown, KingLeft, KingRight,KingTrap
};
class TuttleKing : public Monster
{
private:
	const float ATTACK_TIME = 20.0f;
	const float TRAP_TIME = 5.0f;
	const float MOVE_TIME = 10.0f;
	const int DAMAGE = 10;
	const int ATTACK_SPEED = 110;
public:
	TuttleKing();
	~TuttleKing();

	void Update() override;
	void Render() override;
	bool MonsterCollisionPlayer(Player* player) override;
	bool MonsterCollisionMonster(Monster* monster) override;

	void SetKingStatus(const KingStatus& status)
	{
		kingStatus = status;
		animation->Play(kingStatus);
	}
	KingStatus GetKingStatus() { return kingStatus; }
	void Damage();
	void SetDamageTag(const int& num) { damageTag = num; }

	int GetDamageTag() { return damageTag; }

	void SetPath(const vector<Vector2>& path) { this->path=path; }

	bool IsPathEmpty() { return path.empty(); }
	
	void Reset() override;
private:
	void Move() override;
	void StatusUpdate() override;

	void AttackTime();
	void TrapDeadTime();
	void LoadAnimation() override;

private:

	int damageTag = -1;
	int healthPoint = 50;
	double timer = 0.0f;
	double attackTimer = 0.0f;
	double moveTimer = 0.0f;
	double trapTimer = 0.0f;
	bool isAttack = false;
	bool isTrap = false;
	bool isDie = false;

	KingStatus kingStatus = KingTrap;
	vector<Vector2> path;
	Vector2 velocity;
	HealthPointBar* healthPointBar;
};