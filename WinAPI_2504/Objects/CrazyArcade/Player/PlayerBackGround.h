#pragma once

enum class PlayerBackGroundType
{
	Basic, Clover, Cute, Dragon, Gold, Green, Hopi
};
class PlayerBackGround : public Transform
{
public:
	PlayerBackGround(Vector2 pos);
	~PlayerBackGround();

	void Render();
	static PlayerBackGroundType GetBackGroundType() { return curType; }
	static void SetBackGroundType(PlayerBackGroundType type) { curType = type; }
	static wstring GetBackGroundTypeToWString(PlayerBackGroundType type);
private:
	void CreateQuad();
	wstring ChangeTypeToWstring(PlayerBackGroundType name);

private:
	static PlayerBackGroundType curType;
	unordered_map<PlayerBackGroundType,Quad*> quads;

};