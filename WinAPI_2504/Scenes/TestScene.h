#pragma once

class TestScene : public Scene
{
public :
	TestScene();
	~TestScene();



	// Scene��(��) ���� ��ӵ�
	void Update() override;

	void Render() override;

private:
	TileMap* map;

};