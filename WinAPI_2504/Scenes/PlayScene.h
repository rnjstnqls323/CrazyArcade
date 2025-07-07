#pragma once

enum StageStatus
{
	Stage1, Stage2, Boss
};
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	void Update() override;
	void Render() override;

	void Start() override;
	void End() override;

	StageStatus GetStageStatus() { return curStatus; }

protected:
	virtual void CreatePlayerMap() = 0;
	void CheckCollision();
	void SpawnBubble();
	void ChangeStage();
	void StartGame() { isStart = true; }
	void SetIsEndTrue() { isEnd = true; }

protected:
	bool isStart = false;
	bool isEnd = false;
	bool isSpawn = false;

	StageStatus curStatus;
	TileMap* map;
	Player* player;
	Index2 playerIndex;
	Index2 preIndex;

};