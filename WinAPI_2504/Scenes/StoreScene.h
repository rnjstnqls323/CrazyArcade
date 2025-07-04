#pragma once

class StoreScene :public Scene
{
public:
	StoreScene();
	~StoreScene();

	void Update() override;
	void Render() override;
	void Start() override;
	void End() override;

private:
	void SpawnBubble();
	void CheckCollision();
private:
	bool isSpawn;
	Index2 playerIndex;

	Player* player;
	TileMap* map;
};