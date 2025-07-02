#pragma once

class TestScene : public Scene
{
public :
	TestScene();
	~TestScene();

	void Update() override;

	void Render() override;
	void GUIRender() override;

	void Start() override;
	void End() override;

private:
	void CheckCollision();


	void SpawnBubble();

private:
	bool isSpawn = false;

	TileMap* map;
	Player* player;
	Index2 playerIndex;
	Index2 preIndex;
};