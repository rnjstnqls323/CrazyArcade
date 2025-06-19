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
	void PushPlayer(const Vector2& overlap, Tile& tile);

	void SpawnBubble();
private:
	bool isSpawn = false;


	TileMap* map;
	Character* player;
	Index2 playerIndex;
	Index2 preIndex;

};