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
	CharacterAnimation* animation;

};