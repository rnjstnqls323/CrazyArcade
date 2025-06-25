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
public:
	Player();
	~Player();

	void Update();
	void Render();

	void Die();
private:
	void Move();
	string CharacterNameToString(CharacterName name);
	void LoadAnimation();
	void CreateAnimation();
	void DeleteAnimation();

	void IdleChange();

private:

	bool isKeyPress = false; //이거 플레이어에서만 있어도됨
	float speed = 200.0f;

	Transform* animationTransform;
	CharacterStatus curStatus = DownIdle;
	static CharacterName character;
	unordered_map<CharacterName, Animation*> animation;
};