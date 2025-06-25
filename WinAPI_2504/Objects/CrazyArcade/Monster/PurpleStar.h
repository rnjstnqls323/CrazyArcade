#pragma once

class PurpleStar :public Monster
{
public:
	PurpleStar();
	~PurpleStar();

	MonsterType GetMonsterType() override { return MonsterType::PurpleStar; }

private:

	void LoadAnimation() override;

};