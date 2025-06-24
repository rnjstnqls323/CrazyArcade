#pragma once

enum KingStatus
{
	KingIdle, KingAttack, KingDamage, KingAngry, KingDie,
	KingUp, KingDown, KingLeft, KingRight,KingTrap
};
class TuttleKing : public Monster
{
public:
	TuttleKing();
	~TuttleKing();

public:
	void Update() override;
	void Render() override;

	void SetKingStatus(KingStatus status) { kingStatus = status; }
	KingStatus GetKingStatus() { return kingStatus; }
private:
	void LoadAnimation() override;

private:
	KingStatus kingStatus = KingTrap;
};