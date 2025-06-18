#pragma once

class TestScene : public Scene
{
public :
	TestScene();
	~TestScene();



	// Scene을(를) 통해 상속됨
	void Update() override;

	void Render() override;

private:
	void CheckCollision();
	void PushPlayer(const Vector2& overlap, Tile& tile);
private:
	TileMap* map;
	Character* player;
};