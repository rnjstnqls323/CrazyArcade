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
	TileMap* map;

};