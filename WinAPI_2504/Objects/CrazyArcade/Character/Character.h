#pragma once

enum CharacterStatus
{
	Idle, MoveUp, MoveDown, MoveLeft, MoveRight, BubbleTrapped,Live, Die // 플레시를 넣을까말까 생성될때
};
class Character :public RectCollider
{
public:
	Character();
	~Character();

	virtual void Update();
	void Render();
	
protected:
	virtual void LoadAnimation();

	virtual void Move();

protected:

	bool isKeyPress = false; //이거 플레이어에서만 있어도됨
	float speed = 200.0f;

	Transform* animationTransform;
	CharacterStatus curStatus = Idle;
	Animation* animation;

	//플레이어구현할때, statusstatic으로 아예 빼버리고 캐릭터 고른거 출력할 수 있게 아 그럼 map이용해야될듯

};