#pragma once


class Player :public Character
{
private:
	enum CharacterName {
		Bazzi, Cappi, Dao, Uni, Marid, Dizni
	};
public:
	Player();
	~Player();

	void Update() override;
	void Render() override;

private:
	string CharacterNameToString(CharacterName name);
	void LoadAnimation() override;
	void CreateAnimation();
	void DeleteAnimation();
private:
	static CharacterName character;
	unordered_map<CharacterName, Animation*> animation;
};