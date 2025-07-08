#pragma once

class BossStageScene : public PlayScene
{
public:
	BossStageScene();
	~BossStageScene();


	void Start() override;
	void End() override;
private:
	void CreatePlayerMap() override;
};