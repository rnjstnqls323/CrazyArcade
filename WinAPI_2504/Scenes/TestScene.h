#pragma once

class TestScene : public Scene
{
public :
	TestScene();
	~TestScene();

	void Update() override;

	void Render() override;

private:
	void CheckCollision();


	void SpawnBubble();

private:
	bool isSpawn = false;

	TuttleKing* king;

	TileMap* map;
	Player* player;
	Index2 playerIndex;
	Index2 preIndex;

	BubbleItem* item;
};