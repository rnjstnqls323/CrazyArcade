#pragma once

enum CharacterStatus
{
	Idle, MoveUp, MoveDown, MoveLeft, MoveRight, BubbleTrapped,CharacterLive, CharacterDie //right,left,up idle어케 구분할지 고민
};
class Character :public RectCollider
{
public:
	Character();
	~Character();

	virtual void Update() {}
	virtual void Render() {}
	
protected:
	virtual void LoadAnimation() {}

	virtual void Move(); //이것도 빼주자

protected:

	bool isKeyPress = false; //이거 플레이어에서만 있어도됨
	float speed = 200.0f;

	Transform* animationTransform;
	CharacterStatus curStatus = Idle;
	Animation* animation;

};