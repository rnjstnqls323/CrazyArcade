#pragma once

class PinkStar :public Monster
{
public:
	PinkStar();
	~PinkStar();

	//void Update() override;


	MonsterType GetMonsterType() override { return MonsterType::PinkStar; }

private:

	void LoadAnimation() override;

};