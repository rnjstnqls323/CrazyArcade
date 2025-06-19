#pragma once

enum CharacterStatus
{
	Idle, MoveUp, MoveDown, MoveLeft, MoveRight, BubbleTrapped,Live, Die // �÷��ø� ������� �����ɶ�
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

	bool isKeyPress = false; //�̰� �÷��̾���� �־��
	float speed = 200.0f;

	Transform* animationTransform;
	CharacterStatus curStatus = Idle;
	Animation* animation;

	//�÷��̾���Ҷ�, statusstatic���� �ƿ� �������� ĳ���� ���� ����� �� �ְ� �� �׷� map�̿��ؾߵɵ�

};