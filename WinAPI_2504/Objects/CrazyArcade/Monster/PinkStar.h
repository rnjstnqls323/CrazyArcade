#pragma once

class PinkStar :public Monster
{
public:
	PinkStar();
	~PinkStar();

	//void Update() override;


	MonsterType GetMonsterType() override { return MonsterType::PurpleStar; }

private:

	void LoadAnimation() override;

};