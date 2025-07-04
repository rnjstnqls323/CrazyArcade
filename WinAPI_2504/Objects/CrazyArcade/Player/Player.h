#pragma once

enum CharacterStatus
{
	UpIdle, DownIdle, LeftIdle, RightIdle, MoveUp, MoveDown, MoveLeft, MoveRight, BubbleTrapped, CharacterDie, CharacterLive //right,left,up idle어케 구분할지 고민
};

class Player :public RectCollider
{
private:
	const float DEAD_TIME = 5.0f;
	const float MAX_SPEED = 300.0f;
public:
	Player();
	~Player();

	void Reset();

	void Update();
	void Render();

	CharacterStatus GetStatus() { return curStatus; }
	
	bool GetIsTrap() { return isTrap; }

	static int GetLucci() { return lucci; }
	static void SetLucci(int lucci) { Player::lucci = lucci; }

	void Die();
	void Trap();
	bool IsDieOrTrap();

	void AddSpeed();
	void AddNeedle(){ needleNum++; }

	static wstring GetWstringCharacter(CharacterName name);
	bool IsHaveNeedle();

	static CharacterName GetCharacter() { return character; }
	static void SetCharacter(CharacterName name) { character = name; }
private:
	void Move();
	string CharacterNameToString(CharacterName name);
	void LoadAnimation();
	void CreateAnimation();
	void DeleteAnimation();

	void IdleChange();
	void StatusUpdate();

	void TrapPlayer();
	void CheckRandom();

private:
	static int lucci;
	int needleNum = 0;
	double timer = 0.0f;
	bool isTrap = false;
	bool isKeyPress = false; 
	CharacterData stat;

	Transform* animationTransform;
	CharacterStatus curStatus = DownIdle;
	static CharacterName character;
	unordered_map<CharacterName, Animation*> animation;
	ShaShak* shashak;
};