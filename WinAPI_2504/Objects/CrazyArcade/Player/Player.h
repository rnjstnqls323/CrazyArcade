#pragma once

enum CharacterStatus
{
	UpIdle, DownIdle, LeftIdle, RightIdle, MoveUp, MoveDown, MoveLeft, MoveRight, BubbleTrapped, CharacterDie, CharacterLive //right,left,up idle어케 구분할지 고민
};
class Player :public RectCollider
{
private:
	enum CharacterName {
		Bazzi, Cappi, Dao, Hook, Marid , EndCharacter// 우니 고민하기
	};
	const float DEAD_TIME = 5.0f;
public:
	Player();
	~Player();

	void Update();
	void Render();

	void SetStatus(CharacterStatus status)
	{ 
		curStatus = status; 
		animation[character]->Play(curStatus);
	} //이걸 계속 외부에서 불러올 이유가있나?
	CharacterStatus GetStatus() { return curStatus; }
	
	bool GetIsTrap() { return isTrap; }
	void Die();
	void Trap();

	bool IsDieOrTrap();
private:
	void Move();
	string CharacterNameToString(CharacterName name);
	void LoadAnimation();
	void CreateAnimation();
	void DeleteAnimation();

	void IdleChange();
	void StatusUpdate();

	void TrapPlayer();

private:
	double timer = 0.0f;
	bool isTrap = false;
	bool isKeyPress = false; 
	float speed = 200.0f;

	Transform* animationTransform;
	CharacterStatus curStatus = DownIdle;
	static CharacterName character;
	unordered_map<CharacterName, Animation*> animation;
};